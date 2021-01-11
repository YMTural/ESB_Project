#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <util/delay.h>

#include "bootcamp/debug.h"
#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART_buffer.h"
#include "bootcamp/UART.h"
#include "bootcamp/arduinoArch.h"
#include "bootcamp/UART_interrupt.h"
#include "bootcamp/adc_temperature.h"
#include "bootcamp/priorityQueueHeap.h"

#include "bootcamp/sinusFunctions/sinusFunction.h"

#define BUFFERSIZE 100

volatile uint16_t currentTime = 0;

volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTransmitbuffer;
volatile circularBuffer_t cReceivebuffer;

volatile priorityQueueHeap_t pQueue;

volatile UART_interrupt_t uBuf;

volatile timeBasedScheduler_t tBScheduler;

/*
void freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  int z = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  char m[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  sprintf(m,"%d",z);
  UART_transmit(255);
  for(uint8_t i = 0; i < 16; i++){
    
    UART_transmit(m[i]);
   
  }
   UART_transmit(255);
}*/

void toggleLed(void){

  PORTB ^= _BV(5);
}

void temperatureMessage(void){


  char message[] = "Die aktuelle Temperatur des Chips betraegt circa: ";
  char num[5] = {0,0,0,0,0};
  for (uint8_t i = 0; i < strlen(message); i++)
  {
    circularBuffer_push(cTransmitbuffer, message[i]);
  }

  uint8_t t = adc_temperature_getTemperature();
  sprintf(num, "%d", t);  
  num[3] = 67;
  num[4] = 32;
  for (uint8_t i = 0; i < 5; i++)
  {
    circularBuffer_push(cTransmitbuffer, num[i]);
  }
  UART_interrupt_transmitFromBufferInit(uBuf, strlen(message)+5);

  
}

void init_temp(void){
  adc_temperature_init();
}

void update_temp(void){
  adc_temperature_fetchTemperature();  
}

void greetingMessage(void){

  char message[] = "Dieses Programm berechnet den Sinus (deg) ihrer eingegebenen Zahl! (Format XXX.XX) ";
  for (uint8_t i = 0; i < strlen(message); i++)
    {
      circularBuffer_overwrite(cTransmitbuffer, message[i]);
    }
  UART_interrupt_transmitFromBufferInit(uBuf, strlen(message));

}

void awaitInput(void){

  UART_interrupt_receiveToBufferInit(uBuf, 8);
}

void calculateSinus(void){
  if(!circularBuffer_empty(cReceivebuffer)){

    uint8_t input;



    char message_1[] = " SIN(";

    char message_2[] = ") = ";

    char dot = '.'; 

    char x[8] = {0, 0, 0, 0, 0, 0};

    char s_res[6] = {0,0,0,0,0,0};

    for (uint8_t i = 0; i < 8; i++)
    {
      circularBuffer_read(cReceivebuffer, &input);
      UART_transmit(input);
      x[i] = input;
    }
  
    //Send Error if Input is unexpected
    if(x[6] != 0x0D || x[7] != 0x0A || x[3] != 0x2E){

      char response[] = "Eingabe entspricht nicht dem Format! ";
      for (uint8_t i = 0; i < strlen(response); i++)
      {
        circularBuffer_overwrite(cTransmitbuffer, response[i]);
      }
      UART_interrupt_transmitFromBufferInit(uBuf, strlen(response));


    }else{

    for (uint8_t i = 0; i < 6; i++)
    {
      s_res[i] = x[i];
    }
    float z = strtod(s_res, NULL);
    
    z = mySinusFunction(z);
    z = ceilf(z * 1000) / 1000; 
    int16_t a = (int) z;

    int16_t f = (z - a) * 1000;
 
    char sd[1];

    sprintf(sd, "%i", a);

    char sf[4];

    sprintf(sf, "%i", f);

    //Apparently avr-gcc does not directly support sprintf for float. Linking before compiling is necessary
    //sprintf(s_res, "%f", z);

    for (uint8_t i = 0; i < strlen(message_1); i++)
    {
      circularBuffer_overwrite(cTransmitbuffer, message_1[i]);
    }

    for (uint8_t i = 0; i < 6; i++)
    {
      circularBuffer_overwrite(cTransmitbuffer, x[i]);
    }
    
    for (uint8_t i = 0; i < strlen(message_2); i++)
    {
      circularBuffer_overwrite(cTransmitbuffer, message_2[i]);  
    }

    for (uint8_t i = 0; i < strlen(sd); i++)
    {
      circularBuffer_overwrite(cTransmitbuffer, sd[i]);
    }

    circularBuffer_overwrite(cTransmitbuffer, dot);

    for (uint8_t i = 0; i < strlen(sf); i++)
    {
      circularBuffer_overwrite(cTransmitbuffer, sf[i]);
    }

  UART_interrupt_transmitFromBufferInit(uBuf, strlen(message_1)  + strlen(message_2) + 6 + 5);
    }
  }
}

void transmit(void){

  UART_interrupt_transmitFromBuffer(uBuf);

}
void receive(void){

  UART_interrupt_receiveToBuffer(uBuf, OVERWRITE);
}

void scheduleCalc(void){


  uint8_t data;
  if(circularBuffer_size(cReceivebuffer) >= 8){
    timeBasedScheduler_addTask(tBScheduler, &awaitInput, 20, currentTime+100);
    timeBasedScheduler_addTask(tBScheduler, &calculateSinus, 50, currentTime);
    timeBasedScheduler_addPeriodicTask(tBScheduler, &scheduleCalc, 243, 600, currentTime, 0);
  }

}

int main(void){

  //Initializing Overhead
  sei();
  
  DDRB = _BV(5);

  pQueue = priorityQueueHeap_init(15);

  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTransmitbuffer = circularBuffer_init(transBuffer, BUFFERSIZE);
  cReceivebuffer = circularBuffer_init(recBuffer, BUFFERSIZE);
  
  tBScheduler = timeBasedScheduler_init(16, pQueue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);

  uBuf = UART_interrupt_init(cReceivebuffer, cTransmitbuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
  
  //Initalizing end

  //Non Periodic tasks

  timeBasedScheduler_addTask(tBScheduler, &init_temp, 255, currentTime);

  timeBasedScheduler_addTask(tBScheduler, &greetingMessage, 255, currentTime);

  timeBasedScheduler_addTask(tBScheduler, &awaitInput, 255, currentTime);

  //Periodic tasks here

  //Blinking
  timeBasedScheduler_addPeriodicTask(tBScheduler, &toggleLed, 15, 250, currentTime, 0);

  //Transmit next item on Buffer 2ms
  timeBasedScheduler_addPeriodicTask(tBScheduler, &transmit,25 ,2 , currentTime + 50, 0);
  
  //Receive next item 1ms
  timeBasedScheduler_addPeriodicTask(tBScheduler, &receive, 245, 1, currentTime, 0);

  //Get update Temperature Sensor
  timeBasedScheduler_addPeriodicTask(tBScheduler, &update_temp, 50, 5000, currentTime, 0);

  //Temperature reading message
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &temperatureMessage, 20, 10000, currentTime+5500, 0);

  //Prepare sinusCalc
  timeBasedScheduler_addPeriodicTask(tBScheduler, &scheduleCalc, 243, 600, currentTime, 0);

  //End tasks


  while (true)
  {
    timeBasedScheduler_schedule(tBScheduler, &currentTime);
  }

}


//Interrupt ISR
ISR(USART_UDRE_vect){

  cli();
  UART_interrupt_setTransmitFlag(uBuf, true);
  UART_disableTransmitInterrupt();
  sei();
}

ISR(USART_TX_vect){

  cli();
  if(UART_interrupt_isTransmitComplete(uBuf)){

    UART_disableTransmitCompleteInterrupt();
  }
  else{

    UART_enableTransmitInterrupt();
  }
  sei();
}

ISR(USART_RX_vect){

  cli();
    UART_disableReceiveInterrupt();
    UART_interrupt_setReceiveFlag(uBuf, true); 
  sei();
}

ISR(TIMER0_COMPA_vect){

  cli();

  //keeps track of the number of ms passed
  timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);
  //iterates over tasks in queue and checks
  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler,currentTime);
  sei();
  }

ISR(ADC_vect){

    cli();
    adc_temperature_temperatureReady = 1;
    sei();
}
//Interrupt ISR end