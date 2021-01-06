#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "bootcamp/debug.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART.h"
#include "bootcamp/UART_lib.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "bootcamp/debug.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART.h"
#include "bootcamp/UART_buffer.h"


#define BUFFERSIZE 5


volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTbuf;
volatile circularBuffer_t cRbuf;

volatile UART_buffer_t uBuf;

int main(void)
{
  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTbuf = circularBuffer_init(transBuffer, BUFFERSIZE);
  cRbuf = circularBuffer_init(recBuffer, BUFFERSIZE);

  uBuf = UART_buffer_init(cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  sei();
  DDRB = _BV(5);

  //Pushing number 0 to 24 in Buffer
  for(uint8_t i = 0; i < BUFFERSIZE; i++){

    circularBuffer_push(cTbuf,i);
  }

  //Initializing transmit of 25 Data units from Buffer 
  UART_buffer_transmitMultipleFromBuffer(uBuf, BUFFERSIZE);

  //Initializing receive of 25 Data units from the UART connection 
  for(uint8_t i = 0; i < BUFFERSIZE; i++){

    UART_buffer_receive(uBuf);
  }
  uint8_t data;
  //Sending received data back
  for(uint8_t i = 0; i < BUFFERSIZE; i++){

    circularBuffer_read(cRbuf, &data);
    circularBuffer_push(cTbuf, data);
  }
  UART_buffer_transmitMultipleFromBuffer(uBuf, BUFFERSIZE);
  
  while (true)
  {

    _delay_ms(250);

  }
}
