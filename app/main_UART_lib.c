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
  _delay_ms(200);
  uint8_t size = 0;
  uint8_t recentElement = 0;
  sei();
  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTbuf = circularBuffer_init(transBuffer, BUFFERSIZE);
  cRbuf = circularBuffer_init(recBuffer, BUFFERSIZE);
  PORTB ^= _BV(5);
  uBuf = UART_lib_init(INTERRUPTBUFFER, cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  uint8_t data;
  //Test Interruptmode
  while (true)
  {
    circularBuffer_push(cTbuf, '.');
    //Is permantely sending dots
    UART_lib_transmit(uBuf, BUFFERSIZE);
    //Receives data if interrupt was raised before
    UART_lib_receive(uBuf, 255, OVERWRITE);


    //Echo input and exit loop when 0xFF is received
    if(circularBuffer_size(cRbuf) > size){
      recentElement = circularBuffer_mostRecentElement(cRbuf);
      UART_transmit(circularBuffer_mostRecentElement(cRbuf));
      size++;
      if(circularBuffer_mostRecentElement(cRbuf) == 0xFF) break;
    }
  }
  //Switch Mode for next Test
  circularBuffer_reset(cTbuf);
  circularBuffer_reset(cRbuf);
  uBuf = UART_lib_init(POLLINGBUFFER, cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  //Prepare Buffer for transmit: 0 - (BUFFERSIZE -1)
  for (uint8_t i = 0; i < BUFFERSIZE; i++)
  {
    circularBuffer_push(cTbuf,i);
  }

  //Test Pollingmode
    size = circularBuffer_size(cRbuf);
    //Transmit whole buffer
    UART_lib_transmit(uBuf, BUFFERSIZE);
    //Receive input 
    UART_lib_receive(uBuf, BUFFERSIZE, PUSH);
    size = circularBuffer_size(cRbuf);

    //Echo input
    for (uint8_t i = 0; i < size; i++)
    {
      circularBuffer_read(cRbuf, &data);    
      UART_transmit(data);
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

    UART_disableTransmitCompleteInterrupt();
    UART_enableTransmitInterrupt();
  }
  sei();
}

ISR(USART_RX_vect){

  cli();
  UART_disableReceiveInterrupt();
  UART_lib_setReceiveFlag(uBuf); 
  sei();
}

