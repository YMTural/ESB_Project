#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include "bootcamp/debug.h"
#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART_buffer.h"
#include "bootcamp/UART.h"
#include "bootcamp/arduinoArch.h"
#include "bootcamp/UART_interrupt.h"
#include "bootcamp/adc_temperature.h"
#include "bootcamp/priorityQueueHeap.h"

volatile uint8_t bufferSize = 25;
volatile uint16_t currentTime = 0;
volatile uint8_t numberOfTransmits = 0;

volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTbuf;
volatile circularBuffer_t cRbuf;

volatile priorityQueueHeap_t pQueue;

volatile UART_buffer_t uBuf;

volatile timeBasedScheduler_t tBScheduler;


void test_blink(void){


  PORTB ^= _BV(5);


}

void test_transmit(void){

  UART_transmit(currentTime/1000);
  //UART_transmit(priorityQueueHeap_peekAt(pQueue,1) -> id);
  //UART_transmit(priorityQueueHeap_size(pQueue));
  //UART_transmit(0);

}

void test_starv(void){

  UART_transmit(255);
    //UART_receive();

  

}

int main(void)
{

  transBuffer = malloc(sizeof(uint8_t)*bufferSize);
  recBuffer = malloc(sizeof(uint8_t)*bufferSize);
  
  cTbuf = circularBuffer_init(transBuffer, bufferSize);
  cRbuf = circularBuffer_init(recBuffer, bufferSize);
  
  uBuf = UART_buffer_init(cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  pQueue = priorityQueueHeap_init(16);

  tBScheduler = timeBasedScheduler_init(16, pQueue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);

  DDRB = _BV(5);

  timeBasedScheduler_addPeriodicTask(tBScheduler, &test_blink, 255,500,currentTime,0);
  timeBasedScheduler_addPeriodicTask(tBScheduler, &test_transmit, 255,1000,currentTime,0);
  timeBasedScheduler_addTask(tBScheduler, test_starv,0,65000);
  priorityQueueHeap_peekAt(pQueue,2) -> id = 5;
  //_delay_ms(2000);
  sei();

  //adc_temperature_init();

  /*UART_interrupt_init(cRbuf,cTbuf);

     for (size_t i = 0; i < bufferSize; i++)
  {
    circularBuffer_push(UART_interrupt_transmitBuffer,i);
  }
 */
 

  while (true)
  {
 

    timeBasedScheduler_schedule(tBScheduler, &currentTime);
    //PORTB ^= _BV(5);
    //_delay_ms(1000);
    //adc_temperature_getTemp();


  }
   

   

}

//Init f??r interrupt_uart
ISR(TIMER0_COMPA_vect){

  cli();

  //keeps track of the number of ms passed
  timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);
  //currentTime++;
  //iterates over tasks in queue and checks
  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler,currentTime);

  sei();
  }


