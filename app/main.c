#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
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

#define BUFFERSIZE 255
const char newlineString[8] PROGMEM = {"\n"};
const char counterMessage[32] PROGMEM = {"Der Counter liegt aktuell bei: "};
volatile uint16_t currentTime = 0;

volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;
volatile uint8_t* prioBuffer;
volatile circularBuffer_t cTransmitbuffer;
volatile circularBuffer_t cReceivebuffer;

volatile priorityQueueHeap_t pQueue;

volatile UART_interrupt_t uBuf;

volatile timeBasedScheduler_t tBScheduler;

volatile uint8_t user_counter;

void sendMessage(char *msg){

  for(uint8_t i = 0; i < strlen(msg); i++){
    circularBuffer_overwrite(cTransmitbuffer, msg[i]);
  }
  UART_interrupt_transmitFromBufferInit(uBuf, strlen(msg));
}
//Must handle flash mem pointer differently
void sendMessage_P(const char *pointerToMsg, int length){

    char message[length + 1];
    strcpy_P(message, pointerToMsg);
    for(uint8_t i = 0; i < length; i++){
      circularBuffer_overwrite(cTransmitbuffer, message[i]);
    }
    UART_interrupt_transmitFromBufferInit(uBuf, length);
}

void freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  int z = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  char m[16];
  sprintf(m,"%d",z);
  sendMessage(m);
}
void incrementCounter(){

  user_counter++;
}
void returnCounter(void){

  char message[4];
  sprintf(message, "%d", user_counter);
  sendMessage_P(counterMessage, strlen(counterMessage));
  sendMessage(message);
  sendMessage_P(newlineString, 1);
}
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
  num[4] = '\n';
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

  char message[] = "Dieses Programm berechnet den Sinus (deg) ihrer eingegebenen Zahl! (Format XXX.XX)\n";
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
      //UART_transmit(input);
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
 
    char sd[1] = {0x30};

    sprintf(sd, "%i", a);

    char sf[5] = {0x30,0x30,0x30,0x30,0x30};

    sprintf(sf, "%i", f);

    //Apparently avr-gcc does not directly support sprintf with the float flag %f. Linking before compiling is necessary
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

    
    //Hier müsste noch eine if abfrage rein um das Minus Zeichen nach vorne zu ziehen.
    for (uint8_t i = 0; i < strlen(sf); i++)
    {
      circularBuffer_overwrite(cTransmitbuffer, sf[i]);
    }
    circularBuffer_overwrite(cTransmitbuffer, '\n');
                                                                                //...+ UserInput + Result
  UART_interrupt_transmitFromBufferInit(uBuf, strlen(message_1)  + strlen(message_2) + 6 + 6 + 1);
  
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
    timeBasedScheduler_addTask(tBScheduler, &awaitInput, 20, 100);
    timeBasedScheduler_addTask(tBScheduler, &calculateSinus, 50, 0);
    timeBasedScheduler_addPeriodicTask(tBScheduler, &scheduleCalc, 243, 600, 0, 0);
  }

}

int main(void){

  //Initializing Overhead
  sei();
  
  DDRB = _BV(5);

  prioBuffer = malloc(sizeof(task)*15);
  pQueue = priorityQueueHeap_init(15, prioBuffer);

  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTransmitbuffer = circularBuffer_init(transBuffer, BUFFERSIZE);
  cReceivebuffer = circularBuffer_init(recBuffer, BUFFERSIZE);
  
  tBScheduler = timeBasedScheduler_init(&currentTime, pQueue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

  uBuf = UART_interrupt_init(cReceivebuffer, cTransmitbuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
  
  //Initalizing end

  //Non Periodic tasks

  timeBasedScheduler_addTask(tBScheduler, &init_temp, 255, currentTime);

  timeBasedScheduler_addTask(tBScheduler, &greetingMessage, 255, 0);

  timeBasedScheduler_addTask(tBScheduler, &awaitInput, 255, 0);

  //Periodic tasks here

  //Increment Counter
  timeBasedScheduler_addPeriodicTask(tBScheduler, &incrementCounter, 15, 1000, currentTime, 0);

  //Send Counter Message
  timeBasedScheduler_addPeriodicTask(tBScheduler, &returnCounter, 15, 5000, currentTime, 0);

  //Blinking
  timeBasedScheduler_addPeriodicTask(tBScheduler, &toggleLed, 15, 250, currentTime, 0);

  //Get update Temperature Sensor
  timeBasedScheduler_addPeriodicTask(tBScheduler, &update_temp, 50, 5000, currentTime, 0);

  //Temperature reading message
  timeBasedScheduler_addPeriodicTask(tBScheduler, &temperatureMessage, 20, 10000, currentTime+5500, 0);

  //Prepare sinusCalc
  timeBasedScheduler_addPeriodicTask(tBScheduler, &scheduleCalc, 243, 1000, 0, 0);

  //Debugging
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &freeRam, 245, 1000, 0, 0);

  //End tasks


  while (true)
  {
    timeBasedScheduler_schedule(tBScheduler);
  }

}


//Interrupt ISR
ISR(USART_UDRE_vect){
  cli();
  UART_interrupt_setTransmitFlag(uBuf, true);
  UART_disableTransmitInterrupt();
  //Schedule next transmit
  timeBasedScheduler_addTask(tBScheduler, &transmit, 240, 0);
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
    timeBasedScheduler_addTask(tBScheduler, &receive, 255, 0); 
  sei();
}

ISR(TIMER0_COMPA_vect){

  cli();

  //keeps track of the number of ms passed
  timeBasedScheduler_incrementTimer(tBScheduler);
  //iterates over tasks in queue and checks
  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler);
  sei();
  }

ISR(ADC_vect){

    cli();
    adc_temperature_temperatureReady = 1;
    sei();
}
//Interrupt ISR end