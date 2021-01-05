#ifndef UART_INTERRUPT_H
#define UART_INTERRUPT_H
#include "bootcamp/debug.h"
#if(DEBUG == 0)
#include <avr/io.h>
#include <avr/interrupt.h>
#include "bootcamp/UART.h"
#endif
#if(DEBUG == 1)
#include "bootcamp/io.h"
#include "bootcamp/interrupt.h"
#endif
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "bootcamp/UART.h"
#include "bootcamp/arduinoArch.h"

typedef enum
{
    PUSH,
    OVERWRITE,
}writeMode;

/**
 * @typedef UART_interrupt
 * @brief   Opaque UART_interrupt structure.
 * 
 * This enables encapsulation: the internals will be implemented in the .c file
 * 
 */

typedef struct UART_interrupt UART_interrupt;


/**
 * @typedef UART_buffer_t
 * @brief  UART_buffer abstract data type interface.
 */

typedef UART_interrupt* UART_interrupt_t;

/**
 * @brief   A data transmission is initiated by
 *          enableling Interrupts 
 *           
 * @param   ubuf
 *  8 bit data which is to be transmitted
 */

void UART_interrupt_transmitFromBufferInit(UART_interrupt_t ubuf, uint8_t count);

/**
 *          The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted into the register and returned
*/
void UART_interrupt_receiveToBufferInit(UART_interrupt_t ubuf, uint8_t count);

void UART_interrupt_receiveToBuffer(UART_interrupt_t ubuf, bool mode);

UART_interrupt_t UART_interrupt_init(void* receiveBuffer, void* transmitBuffer,
                            void (*circularBuffer_overwrite)(void* cbuf, uint8_t data), 
                            int8_t (*circularBuffer_push)(void* cbuf, uint8_t data),
                            int8_t (*circularBuffer_read)(void* cbuf, uint8_t* data) );



void UART_interrupt_transmitFromBuffer(UART_interrupt_t ubuf);

void UART_interrupt_setTransmitFlag(UART_interrupt_t ubuf, bool status);

bool UART_interrupt_isTransmitComplete(UART_interrupt_t ubuf);

bool UART_interrupt_isReceiveComplete(UART_interrupt_t ubuf);

void UART_interrupt_setReceiveFlag(UART_interrupt_t ubuf, bool status);


#endif