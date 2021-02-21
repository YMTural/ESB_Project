#include "bootcamp/interrupt.h"

char EICRA = 0;
char EIMSK = 0;
char TCNT0 = 0;
char TCCR0A = 0;
char WGM01 = 0;
char OCR0A = 0;
char TIMSK0 = 0;
char OCIE0A = 0;
char TCCR0B = 0;
char CS01 = 0;
char CS00 = 0;
//temperature reading
char ADCW = 0;
char ADMUX = 0;
char REFS1 = 0;
char REFS0 = 0;
char MUX3 = 0;
char ADEN = 0;
char ADIE = 0;
char ADPS2 = 0;
char ADPS1 = 0;
char ADPS0 = 0;
char ADCSRA = 0;
char ADSC = 0;

char CS10 = 0;
char WGM12 = 0;
char TCNT1 = 0;
char TCCR1B = 0;
char TIMSK1 = 0;
short OCR1B = 0;
short OCR1A = 0;
char OCIE1A = 0;
char OCIE1B = 0;
char CS12 = 0;
char CS11 = 0;
void sei(void){

    //no-op
}
void cli(void){

    //no-op
}