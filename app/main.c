#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART.h"

int
main(void)
{
  uint8_t data;
  uint8_t* transBuffer = malloc(sizeof(uint8_t)*4);
  uint8_t* recBuffer = malloc(sizeof(uint8_t)*4);
  UART_init(MYUBRR);
  circularBuffer_t cTbuf = circularBuffer_init(transBuffer, 4);
  circularBuffer_t cRbuf = circularBuffer_init(recBuffer, 4);
  circularBuffer_push(cTbuf,10);
  UART_transmit(cTbuf, *circularBuffer_read,&data);
    

  DDRB = _BV(5);
  while (true)
  {
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(1000);
    PORTB ^= _BV(5);
  }
}
