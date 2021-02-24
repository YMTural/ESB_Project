#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "bootcamp/debug.h"
#include "bootcamp/UART.h"



int main(void)
{
  UART_init(MYUBRR);

  //Sends Numbers from 0 to 255 as hex to the receiver
  //Polling based transmit
  for (uint16_t i = 0; i < 256; i++)
  {
    UART_transmit(i);
  }

  //Receives Numbers from 0 to 255 as hex from the transmiter and sends them back incremented
  //Polling based receive
  for (uint16_t i = 0; i < 256; i++)
  {
    UART_transmit(UART_receive()+1);
  }

  DDRB = _BV(5);
  PORTB ^= _BV(5);
}
