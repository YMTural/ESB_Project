#ifndef ARDUINOARCH
#define ARDUINOARCH
#include "bootcamp/debug.h"
#include <stdint.h>
#if DEBUG == 1
#include "bootcamp/interrupt.h"
#include "bootcamp/io.h"
#endif
#if DEBUG == 0
#include <avr/interrupt.h>
#include <avr/io.h>
#endif


/**
 * @brief
 *  Sets an internal timer which raises an interrupt every 1ms
 * 
 * 
 */
void arduinoArch_setTimer(void);

/**
 * @brief
 *  Initializes interrupt based temperature reading by setting the required bits in the register
 * 
 * 
 */
void arduinoArch_temperature_init(void);


/**
 * @brief
 *  Requests temperature to be calculated.  
 * 
 * 
 */ 
void arduinoArch_fetchTemperature(void);

/**
 * @brief
 *  Returns the corresponding register regarding the temperature
 * 
 * @return
 *  Value of ADCW (pseudoregister)
 */ 
uint16_t arduinoArch_getTemperatureRegister(void);

void arduinoArch_PWMTimerinit(void);

void arduinoArch_PWMTimerStop(void);

#endif