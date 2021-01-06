#ifndef UART_LIB_H
#define UART_LIB_H

#include "bootcamp/UART.h"
#include "bootcamp/UART_interrupt.h"
#include "bootcamp/UART_buffer.h"


typedef enum
{
    POLLINGBUFFER,
    INTERRUPTBUFFER
}UARTMode;

typedef struct UART_lib UART_lib;

typedef UART_lib* UART_lib_t;

/**
 * @brief
 *  Initializes UART connection depending on the mode
 * 
 * @param   receiveBuffer
 *  Storage buffer for the elements to be received, must be created independently
 * 
 * @param   transmitBuffer
 *  Storage buffer for the elements to be transmitted, must be created independently
 * 
 * @param   circularBuffer_overwrite
 *  Pointer to a buffer overwrite function
 * 
 * @param   circularBuffer_push
 *  Pointer to buffer push function
 * 
 * @param circularBuffer_read
 *  Pointer to buffer read function
 * 
 * @returns
 *  A UART lib handle
 */
UART_lib_t UART_lib_init(uint8_t mode, void* receiveBuffer, void* transmitBuffer,
    void(*circularBuffer_overwrite)(void* cbuf, uint8_t data),
    int8_t (*circularBuffer_push)(void* cbuf, uint8_t data),
    int8_t(*circularBuffer_read)(void* cbuf, uint8_t* data ));

/**
 * @brief   A data transmission is initiated by
 *          loading the transmit register with data
 *          from the buffer. N data in the buffer will be transmitted
 */
void UART_lib_transmit(UART_lib_t ubuf, uint8_t count);

/**
 * @brief   The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted from the register
 *          into the buffer. 0 on success, -1 if failed        
 */   
void UART_lib_receive(UART_lib_t ubuf, uint16_t count, uint8_t receiveMode);


void UART_lib_setTransmitFlag(UART_lib_t ubuf);

uint8_t UART_lib_isTransmitComplete(UART_lib_t ubuf);

uint8_t UART_lib_isReceiveComplete(UART_lib_t ubuf);

void UART_lib_setReceiveFlag(UART_lib_t ubuf);




#endif