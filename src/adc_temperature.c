#include "bootcamp/adc_temperature.h"
#include "bootcamp/UART.h"


void adc_temperature_init(void){

    ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

}

void adc_temperature_getTemp(void){

    ADCSRA |= (1 << ADSC);


}

ISR(ADC_vect){

    cli();
    uint16_t wADC = ADCW;
    //Temperature calculation according to https://playground.arduino.cc/Main/InternalTemperatureSensor/ :temperature = (ADCW - 324.31) / 1.22
    uint32_t t = 4*(wADC - 324) / 5;

    UART_transmit(t);
    sei();
}