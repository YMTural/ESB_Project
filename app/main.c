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

volatile uint8_t bufferSize = 25;
volatile uint16_t currentTime = 0;
volatile uint8_t numberOfTransmits = 0;

volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTbuf;
volatile circularBuffer_t cRbuf;

volatile UART_buffer_t uBuf;

volatile timeBasedScheduler_t tBScheduler;


void test_blink(void){


  PORTB ^= _BV(5);


}

void test_transmit(void){

  //UART_transmit(currentTime);
  UART_transmit(0);

}

void test_starv(void){

  for (size_t i = 0; i < 255; i++)
  {
    //UART_receive();
  }
  

}

int main(void)
{

  transBuffer = malloc(sizeof(uint8_t)*bufferSize);
  recBuffer = malloc(sizeof(uint8_t)*bufferSize);
  
  cTbuf = circularBuffer_init(transBuffer, bufferSize);
  cRbuf = circularBuffer_init(recBuffer, bufferSize);
  
  uBuf = UART_buffer_init(cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  tBScheduler = timeBasedScheduler_init(16);

  DDRB = _BV(5);

  //timeBasedScheduler_addPeriodicTask(tBScheduler, &test_blink, 255,500,currentTime);
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &test_transmit, 255,1000,currentTime);
  //timeBasedScheduler_addTask(tBScheduler, test_starv,0,1000);
  //_delay_ms(2000);
  sei();

  adc_temperature_init();

  UART_interrupt_init(cRbuf,cTbuf);

     for (size_t i = 0; i < bufferSize; i++)
  {
    circularBuffer_push(UART_interrupt_transmitBuffer,i);
  }

 

  while (true)
  {
 

    //timeBasedScheduler_schedule(tBScheduler, &currentTime);
    PORTB ^= _BV(5);
    _delay_ms(1000);
    //adc_temperature_getTemp();


  }
   

   

}

//Init für interrupt_uart
ISR(TIMER0_COMPA_vect){

  cli();
  //keeps track of the number of ms passed
  currentTime++;
  //timeBasedScheduler_markIfReady(tBScheduler);
  //iterates over tasks in queue and checks
  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler,currentTime);
  sei();
  }


