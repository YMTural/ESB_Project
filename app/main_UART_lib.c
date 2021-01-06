#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "bootcamp/debug.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART.h"
#include "bootcamp/UART_lib.h"

#define BUFFERSIZE 5

volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTbuf;
volatile circularBuffer_t cRbuf;

volatile UART_lib_t uBuf;



int main(void)
{
  uint8_t x = 0;
  sei();
  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTbuf = circularBuffer_init(transBuffer, BUFFERSIZE);
  cRbuf = circularBuffer_init(recBuffer, BUFFERSIZE);
  
  uBuf = UART_lib_init(INTERRUPTBUFFER, cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
  for (uint8_t i = 0; i < BUFFERSIZE; i++)
  {
    circularBuffer_push(cTbuf, i);
  }
  uint8_t data;
/*
  for (uint8_t i = 0; i < BUFFERSIZE; i++)
  {
    circularBuffer_read(cRbuf, &data);
    UART_transmit(data);
  }
*/
  while (true)
  {
    //UART_lib_transmit(uBuf, BUFFERSIZE);
    //UART_lib_receive(uBuf, BUFFERSIZE, PUSH);
    PORTB ^= _BV(5);
    x++;
    circularBuffer_push(cTbuf, x);

    UART_lib_receive(uBuf, 25, OVERWRITE);

    //Send 0xFF when all the expected data has been received
    if(circularBuffer_full(cRbuf)){
      UART_transmit(255);
    }
  }

  return 0;
}

ISR(USART_UDRE_vect){

  cli();
  UART_lib_setTransmitFlag(uBuf);
  UART_disableTransmitInterrupt();
  sei();
}

ISR(USART_TX_vect){

  cli();
  if(UART_lib_isTransmitComplete(uBuf)){

    UART_disableTransmitCompleteInterrupt();
  }
  else{

    UART_enableTransmitInterrupt();
  }
  sei();
}

ISR(USART_RX_vect){

  cli();
  if(UART_lib_isReceiveComplete(uBuf)){
    UART_disableReceiveInterrupt();
  }
  else{
    UART_disableReceiveInterrupt();
    UART_lib_setReceiveFlag(uBuf); 
  }
  sei();
}