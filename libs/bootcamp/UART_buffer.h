#ifndef UART_BUFFER_H
#define UART_BUFFER_H

#include "bootcamp/debug.h"
#include "bootcamp/UART.h"
#include "stdbool.h"




/**
 * @typedef UART_buffer
 * @brief   Opaque UART_buffer structure.
 * 
 * This enables encapsulation: the internals will be implemented in the .c file
 * 
 */

typedef struct UART_buffer UART_buffer;


/**
 * @typedef UART_buffer_t
 * @brief  UART_buffer abstract data type interface.
 */

typedef UART_buffer* UART_buffer_t;

/**
 * @brief   Creates UART_buffer container.
 * 
 *  Read, push functions and buffers are contained here.
 * 
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
 *  A UART buffer handle
 */
UART_buffer_t UART_buffer_init(uint8_t* receiveBuffer, uint8_t* transmitBuffer,
                             void (*circularBuffer_overwrite)(uint8_t* cbuf, uint8_t data), 
                             bool (*circularBuffer_push)(uint8_t* cbuf, uint8_t data),
                             int8_t (*circularBuffer_read)(uint8_t* cbuf, uint8_t* data));


/**
 * @brief   The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted from the register
 *          into the buffer overwriting old data if necessary.       
 */
void UART_buffer_overwriteReceive(UART_buffer_t ubuf);


/**
 * @brief   The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted from the register
 *          into the buffer. 0 on success, -1 if failed           
 */
bool UART_buffer_receive(UART_buffer_t ubuf);

/**
 * @brief   A data transmission is initiated by
 *          loading the transmit register with data
 *          from the buffer. All data in the buffer will be transmitted
 *           
 */
int8_t UART_buffer_transmitFromBuffer(UART_buffer_t ubuf);

/**
 * @brief   A data transmission is initiated by
 *          loading the transmit register with data
 *          from the buffer. N data in the buffer will be transmitted
 * @return
 *  -1 if failed, 0 on success
 */
int8_t UART_buffer_transmitMultipleFromBuffer(UART_buffer_t ubuf, uint8_t count);

/**
 * @brief   Frees a circular buffer structure.
 * 
 * 
 * @param   UART_buffer
 *  Uart buffer to be freed
 */
void UART_buffer_free(UART_buffer_t UART_buffer);

#endif