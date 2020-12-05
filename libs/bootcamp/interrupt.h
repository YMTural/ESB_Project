#ifndef INTERRUPT_MOCK
#define INTERRUPT_MOCK

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

void sei(void);





#endif