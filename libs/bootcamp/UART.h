#ifndef UART_H
#define UART_H
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


#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)



/**
 * @brief   Initializes UART protocol.
 *          Using Polling, fixed frame of 8
 *          Data, 1 start and 1 stop bit.
 * 
 * @param   ubrr
 *  Baud Rate Register Value
 */
void UART_init(unsigned int ubrr);


/**
 * @brief   A data transmission is initiated by
 *          loading the transmit register with data
 *          which is to be transmitted.
 *           
 * @param   data
 *  8 bit data which is to be transmitted
 */

void UART_transmit(uint8_t data);

/**
 *          The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted into the register and returned
*/
uint8_t UART_receive(void);


/**
 * @brief   The receiver registerbuffer FIFO will be flushed when
 *          the receiver is disabled and unread data will
 *          be lost        
 */
void UART_flush(void);


void UART_enableTransmitInterrupt(void);

void UART_disableTransmitInterrupt(void);

void UART_enableReceiveInterrupt(void);

void UART_disableReceiveInterrupt(void);

void UART_enableTransmitCompleteInterrupt(void);

void UART_disableTransmitCompleteInterrupt(void);

void UART_overwriteRegister(uint8_t data);

uint8_t UART_forceReadData(void);
#endif