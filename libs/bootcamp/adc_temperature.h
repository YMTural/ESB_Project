#ifndef ADC_TEMPERATURE_H
#define ADC_TEMPERATURE_H


#include <avr/io.h>
#include <avr/interrupt.h>

void adc_temperature_init(void);


void adc_temperature_getTemp(void);

#endif