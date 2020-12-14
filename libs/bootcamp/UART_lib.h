#ifndef UART_LIB_H
#define UART_LIB_H

#if UART_INTERRUPT == 1
#include "bootcamp/UART_interrupt.h"
#endif
#if UART_INTERRUPT == 0
#include "bootcamp/UART_buffer.h"
#endif