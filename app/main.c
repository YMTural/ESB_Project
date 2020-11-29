#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART.h"

int
main(void)
{
  
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
