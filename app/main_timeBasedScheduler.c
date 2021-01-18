#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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

#define BUFFERSIZE 45

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

void test_message(void){

  cli();
  char message[38] = "Der aktuelle Stand des Timers lautet: ";

  for (uint8_t i = 0; i < 38; i++)
  {
   circularBuffer_push(cTransmitbuffer, message[i]);
  }
  char num[4];
  uint8_t time = currentTime/1000;
  sprintf(num, "%i", time);  
  num[2] = 115;
  num[3] = 32;
  
  for (uint8_t i = 0; i < 4; i++)
  {
    circularBuffer_push(cTransmitbuffer, num[i]);
  }
  UART_interrupt_transmitFromBufferInit(uBuf, 42);
  sei();
}

void transmit(void){
  cli();
  UART_interrupt_transmitFromBuffer(uBuf);
  sei();
}


int main(void){

  //Initializing Overhead
  sei();
  
  DDRB = _BV(5);

  pQueue = priorityQueueHeap_init(8);

  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTransmitbuffer = circularBuffer_init(transBuffer, BUFFERSIZE);
  cReceivebuffer = circularBuffer_init(recBuffer, BUFFERSIZE);
  
  tBScheduler = timeBasedScheduler_init(16, pQueue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

  uBuf = UART_interrupt_init(cReceivebuffer, cTransmitbuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  //Initalizing end





  //Periodic tasks here

  //Blinking
  timeBasedScheduler_addPeriodicTask(tBScheduler, &toggleLed, 26, 250, currentTime, 0);

  timeBasedScheduler_addPeriodicTask(tBScheduler, &transmit,24 ,1 , 50, 0);
  
  timeBasedScheduler_addPeriodicTask(tBScheduler, &test_message, 25, 1000, currentTime, 0);

  
  //End Periodic tasks

  //Main Loop
  while (true)
  {
    timeBasedScheduler_schedule(tBScheduler, &currentTime);
  }
  //Main Loop end




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

//Interrupt ISR end