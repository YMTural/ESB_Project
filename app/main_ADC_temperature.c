#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "bootcamp/debug.h"
#include "bootcamp/UART.h"
#include "bootcamp/adc_temperature.h"


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
    //Request Temperature
    adc_temperature_fetchTemperature();
    //Check if temperature reading is ready
    if(adc_temperature_temperatureReady){
        //Get temperature and transmit via UART (hex)
       UART_transmit(adc_temperature_getTemperature());
    }
  }
}


ISR(ADC_vect){

    cli();
    adc_temperature_temperatureReady = 1;
    sei();
}