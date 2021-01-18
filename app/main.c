
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "bootcamp/debug.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART.h"
#include "bootcamp/UART_interrupt.h"


#define BUFFERSIZE 255


volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTbuf;
volatile circularBuffer_t cRbuf;

volatile UART_interrupt_t uBuf;

int main(void)
{
  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTbuf = circularBuffer_init(transBuffer, BUFFERSIZE);
  cRbuf = circularBuffer_init(recBuffer, BUFFERSIZE);

  uBuf = UART_interrupt_init(cRbuf, cTbuf, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  sei();
  DDRB = _BV(5);

  //Pushing number 0 to 24 in Buffer
  for(uint8_t i = 0; i < BUFFERSIZE; i++){

    //circularBuffer_push(cTbuf,i);
  }

  //Initializing transmit of 25 Data units from Buffer 
  UART_interrupt_transmitFromBufferInit(uBuf, 255);

  //Initializing receive of 25 Data units from the UART connection 
  UART_interrupt_receiveToBufferInit(uBuf, 255);

  uint8_t data;
 
  while (true)
  {
    //Sending Data whenever the transmit register is ready
    UART_interrupt_transmitFromBuffer(uBuf);
    PORTB ^= _BV(5);
    //_delay_ms(250);
    UART_interrupt_receiveToBuffer(uBuf, OVERWRITE);
    if(!circularBuffer_read(cRbuf, &data)){
      circularBuffer_push(cTbuf, data);
    }


    //Send 0xFF when all the expected data has been received
    if(circularBuffer_full(cRbuf)){

      UART_transmit(255);
    }

  }
}

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
    UART_disableTransmitCompleteInterrupt();
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