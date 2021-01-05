#include "bootcamp/adc_temperature.h"
#include "bootcamp/UART.h"

uint8_t adc_temperature;

void adc_temperature_init(void){

    ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

}

void adc_temperature_fetchTemperature(void){

    ADCSRA |= (1 << ADSC);
}

uint8_t adc_temperature_getTemperature(void){

    return adc_temperature;
}

ISR(ADC_vect){

    cli();
    uint16_t wADC = ADCW;
    //Temperature calculation according to https://playground.arduino.cc/Main/InternalTemperatureSensor/ :temperature = (ADCW - 324.31) / 1.22
    uint32_t t = 4*(wADC - 324) / 5;
    adc_temperature = t;
    //UART_transmit(t);
    sei();
}