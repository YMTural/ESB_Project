#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#ifndef DEBUG
#define DEBUG 0
#endif
#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART_buffer.h"
#include "bootcamp/UART.h"



uint8_t bufferSize = 4;
volatile uint16_t currentTime = 0;

volatile timeBasedScheduler_t tBScheduler;

void test_blink(void){


  PORTB ^= _BV(5);


}

void test_transmit(void){

  UART_transmit(currentTime);


}

int main(void)
{
  
  uint8_t data;
  
  uint8_t* transBuffer = malloc(sizeof(uint8_t)*bufferSize);
  uint8_t* recBuffer = malloc(sizeof(uint8_t)*bufferSize);
  
  circularBuffer_t cTbuf = circularBuffer_init(transBuffer, bufferSize);
  circularBuffer_t cRbuf = circularBuffer_init(recBuffer, bufferSize);
  
  UART_buffer_t uBuf = UART_buffer_init(cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);


  tBScheduler = timeBasedScheduler_init(16);
  DDRB = _BV(5);

  timeBasedScheduler_addPeriodicTask(tBScheduler, &test_blink, 0,3000,currentTime);
  timeBasedScheduler_addPeriodicTask(tBScheduler, &test_transmit, 255,500,currentTime);

  while (true)
  {
    
    timeBasedScheduler_schedule(tBScheduler, &currentTime);

    }
   

   

}



ISR(TIMER0_COMPA_vect){
  //keeps track of the number of ms passed
  currentTime++;
  //timeBasedScheduler_markIfReady(tBScheduler);
  //iterates over tasks in queue and checks
  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler,currentTime);
  }
