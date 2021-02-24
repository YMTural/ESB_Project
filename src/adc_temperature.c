#include "bootcamp/adc_temperature.h"
#include "bootcamp/arduinoArch.h"
//#include "bootcamp/UART.h"


volatile int8_t adc_temperature_temperatureReady = 0;

void adc_temperature_init(void){

    arduinoArch_temperature_init();
}

void adc_temperature_fetchTemperature(void){

    arduinoArch_fetchTemperature();
}

uint8_t adc_temperature_getTemperature(void){

    uint16_t wADC = arduinoArch_getTemperatureRegister();
    //Temperature calculation according to https://playground.arduino.cc/Main/InternalTemperatureSensor/ :temperature = (ADCW - 324.31) / 1.22
    uint32_t t = 4*(wADC - 324) / 5;
    adc_temperature_temperatureReady = 0;
    return t;
}

/*
ISR(ADC_vect){

    cli();
    adc_temperature_temperatureReady = 1;
    sei();
}
*/