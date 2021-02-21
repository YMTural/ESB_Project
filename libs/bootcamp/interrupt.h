#ifndef INTERRUPT_MOCK
#define INTERRUPT_MOCK
#include "bootcamp/debug.h"

extern char EICRA;
extern char EIMSK;
extern char TCNT0;
extern char TCCR0A;
extern char WGM01;
extern char OCR0A;
extern char TIMSK0;
extern char OCIE0A;
extern char TCCR0B;
extern char CS01;
extern char CS00;

extern char ADCW;
extern char ADCW;
extern char ADMUX;
extern char REFS1;
extern char REFS0;
extern char MUX3;
extern char ADEN;
extern char ADIE;
extern char ADPS2;
extern char ADPS1;
extern char ADPS0;
extern char ADCSRA;
extern char ADSC;

extern char CS10;
extern char WGM12;
extern char TCNT1;
extern char TCCR1B;
extern char TIMSK1;
extern short OCR1B;
extern short OCR1A;
extern char OCIE1A;
extern char OCIE1B;
extern char CS12;
extern char CS11;
void sei(void);


void cli(void);


#endif