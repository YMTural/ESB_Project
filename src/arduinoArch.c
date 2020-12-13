#include "bootcamp/arduinoArch.h"

void arduinoArch_setTimer(){
    TCNT0=0;
    //Sets CTC mode
    TCCR0A=(1<<WGM01);
    //Sets top value for output compare 
    OCR0A=250;
    //Enable interrupt for output compare 
    TIMSK0=(1<<OCIE0A);
    //Selects Prescaler 64 and start timer0
    TCCR0B=(1<<CS01)|(1<<CS00);

}



