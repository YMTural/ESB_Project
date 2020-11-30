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
  //circularBuffer_push(cTbuf,255);
  //UART_transmit(cTbuf, *circularBuffer_read);
  _delay_ms(100);  

  DDRB = _BV(5);
  while (true)
  {
    /*
    _delay_ms(100);
    circularBuffer_push(cTbuf,0);
    _delay_ms(100);
    UART_transmit(cTbuf, *circularBuffer_read);
    _delay_ms(100);
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(400);
    //PORTB ^= _BV(5);
    circularBuffer_push(cTbuf,128);
    _delay_ms(100);
    UART_transmit(cTbuf, *circularBuffer_read);
  */
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = 10;
    _delay_ms(100);
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(400);
    while (!(UCSR0A & (1<<UDRE0)));
    //UDR0 = 0;
    _delay_ms(100);
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(200);
    PORTB ^= _BV(5);
    _delay_ms(400);
  }
}
