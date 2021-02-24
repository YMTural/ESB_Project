
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



  //Initializing receive of 255 Data units from the UART connection 
  UART_interrupt_receiveToBufferInit(uBuf, 255);

  uint8_t data;
  PORTB ^= _BV(5);
  while (true)
  {
    //Constantly sending dots
    circularBuffer_push(cTbuf, '.');
    UART_interrupt_transmitFromBufferInit(uBuf, 1);
    //Sending Data whenever the transmit register is ready
    UART_interrupt_transmitFromBuffer(uBuf);
    //Receiving whenever data is present
    UART_interrupt_receiveToBuffer(uBuf, OVERWRITE);
    //If data has been received toggle Led and send echo
    if(!circularBuffer_read(cRbuf, &data)){
      PORTB ^= _BV(5);
      UART_transmit(data);
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