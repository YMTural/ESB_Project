#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART_buffer.h"
#include "bootcamp/UART.h"

#ifndef DEBUG
#define DEBUG 0
#endif

uint8_t bufferSize = 4;

int main(void)
{
  
  uint8_t data;

  uint8_t* transBuffer = malloc(sizeof(uint8_t)*bufferSize);
  uint8_t* recBuffer = malloc(sizeof(uint8_t)*bufferSize);
  
  circularBuffer_t cTbuf = circularBuffer_init(transBuffer, bufferSize);
  circularBuffer_t cRbuf = circularBuffer_init(recBuffer, bufferSize);
  
  UART_buffer_t uBuf = UART_buffer_init(cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
  //circularBuffer_push(cTbuf,255);
  //UART_transmit(cTbuf, *circularBuffer_read);
  _delay_ms(100);  
  uint8_t test = 10;
  uint8_t test2 =128;
  DDRB = _BV(5);
  while (true)
  {
    
    UART_buffer_receive(uBuf);
    circularBuffer_read(cRbuf, &test2);
    _delay_ms(500);
    //PORTB ^= _BV(5);
    


    }
   

  } 

}
