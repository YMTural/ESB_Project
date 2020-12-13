#ifndef UART_INTERRUPT_H
#define UART_INTERRUPT_H
#include "bootcamp/debug.h"
#if(DEBUG == 0)
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#if(DEBUG == 1)
#include "bootcamp/io.h"
#include "bootcamp/interrupt.h"
#endif
#include <stdlib.h>
#include <stdint.h>
#include "bootcamp/UART.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/arduinoArch.h"
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)

volatile uint8_t UART_interrupt_tCounter;
volatile uint8_t UART_interrupt_rCounter;

volatile uint8_t UART_interrupt_data;

volatile uint8_t* UART_interrupt_receiveBuffer;   

volatile uint8_t* UART_interrupt_transmitBuffer;
/**
 * @brief   A data transmission is initiated by
 *          loading the transmit register with data from the buffer
 *          which is to be transmitted.
 *           
 * @param   data
 *  8 bit data which is to be transmitted
 */

void UART_interrupt_transmitFromBuffer(circularBuffer_t transmitBuffer, uint8_t count);

/**
 *          The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted into the register and returned
*/
uint8_t UART_interrupt_receiveToBuffer(circularBuffer_t transmitBuffer, uint8_t count);

void UART_interrupt_init(uint8_t* receiveBuffer, uint8_t* transmitBuffer);


#endif