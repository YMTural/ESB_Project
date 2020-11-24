#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int
main(void)
{
  DDRB = _BV(5);
  while (true)
  {
    _delay_ms(750);
    PORTB ^= _BV(5);
  }
}