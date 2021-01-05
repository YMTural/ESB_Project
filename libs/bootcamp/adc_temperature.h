#ifndef ADC_TEMPERATURE_H
#define ADC_TEMPERATURE_H
#include "bootcamp/debug.h"
#if DEBUG == 0
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#if DEBUG == 1
#include "bootcamp/io.h"
#include "bootcamp/interrupt.h"
#endif
void adc_temperature_init(void);

uint8_t adc_temperature_getTemperature(void);

void adc_temperature_fetchTemperature(void);

#endif