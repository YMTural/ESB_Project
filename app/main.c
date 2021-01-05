
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "bootcamp/debug.h"
#include "bootcamp/UART.h"
#include "bootcamp/adc_temperature.h"


#define BUFFERSIZE 25

int main(void)
{
  UART_init(MYUBRR);
  sei();
  adc_temperature_init();
  DDRB = _BV(5);

  while (true)
  {

    PORTB ^= _BV(5);
    _delay_ms(250);
    adc_temperature_fetchTemperature();
    UART_transmit(adc_temperature_getTemperature());
  }
}

