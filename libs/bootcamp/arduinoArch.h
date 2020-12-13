#ifndef ARDUINOARCH
#define ARDUINOARCH
#include "bootcamp/debug.h"
#if DEBUG == 1
#include "bootcamp/interrupt.h"
#include "bootcamp/io.h"
#endif
#if DEBUG == 0
#include <avr/interrupt.h>
#include <avr/io.h>
#endif

//Needs documentation; Set timer to 1ms
void arduinoArch_setTimer(void);

#endif