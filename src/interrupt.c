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



void sei(void){

    //no-op
}
void cli(void){

    //no-op
}