#ifndef ADC_TEMPERATURE_H
#define ADC_TEMPERATURE_H
#include "bootcamp/debug.h"
#include "stdint.h"
#if DEBUG == 0
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#if DEBUG == 1
#include "bootcamp/io.h"
#include "bootcamp/interrupt.h"
#endif

//Bool for ISR
extern volatile int8_t adc_temperature_temperatureReady;

/**
 * @brief
 *  Initializes interrupt based temperature reading by setting the required bits in the register
 * 
 * 
 */
void adc_temperature_init(void);

/**
 * @brief
 *  Returns the most recent temperature reading from the sensor as hex
 * 
 * @return
 *  Temperature from the sensor as hex. Returns FF when trying to read the value when it is not ready.
 * 
 */ 

uint8_t adc_temperature_getTemperature(void);

/**
 * @brief
 *  Requests temperature to be calculated.  
 * 
 * 
 */ 

void adc_temperature_fetchTemperature(void);

#endif