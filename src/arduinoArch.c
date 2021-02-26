#include "bootcamp/arduinoArch.h"

void arduinoArch_setTimer(){
    TCNT2 = 0;
    OCR2A  = 125 -1;
    TCCR2A = (1 << WGM21);
    TIMSK2 = (1 << OCIE2A);
    TCCR2B = (1 << CS20) | (1 << CS22);
}

void arduinoArch_PWMTimerinit(void){
    //Counter value init to 0
    TCNT1 = 0;
    //Sets CTC mode and clock with no prescaling
    TCCR1B |= (1<<CS10) | (1<<WGM12);
    //Enable interrupt for output compare
    TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B);

    OCR1A = 257; 
    OCR1B = 0;

}

void arduinoArch_PWMTimerStop(void){

    TCCR1B &= ~(1<< CS12);  // turn off the clock altogether
    TCCR1B &= ~(1<< CS11);
    TCCR1B &= ~(1<< CS10);
    TCNT1 = 0;
    TIMSK1 &= ~(1<<OCIE1A);
    TIMSK1 &= ~(1<<OCIE1B);
}

void arduinoArch_temperature_init(void){

    ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void arduinoArch_fetchTemperature(void){

    ADCSRA |= (1 << ADSC);
}

uint16_t arduinoArch_getTemperatureRegister(void){

    uint16_t wADC = ADCW;
    return wADC;
}


