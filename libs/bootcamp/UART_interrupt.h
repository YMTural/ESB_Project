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
 * @typedef UART_interrupt_t
 * @brief  UART_buffer abstract data type interface.
 */

typedef UART_interrupt* UART_interrupt_t;

/**
 * @brief   A data transmission is initiated by
 *          enableling Interrupts 
 *           
 * @param   ubuf
 *  Uart_interrupt handler
 * @param count
 *  Amount of planned transmits
 */

void UART_interrupt_transmitFromBufferInit(UART_interrupt_t ubuf, uint8_t count);

/**
 * @brief A data reception is initiated by enableing the receive interrupt
 * 
 * @param ubuf
 * Uart_interrupt handler
 * @param
 * Amount of expected receives
*/
void UART_interrupt_receiveToBufferInit(UART_interrupt_t ubuf, uint8_t count);

/**
 * @brief
 *  If the RX_VECT interrupt has been called, the contents of the receive buffer register are 
 *  read and pushed/overwritten into the buffer
 * @param ubuf
 * Uart_interrupt handler
 * @param mode
 * Type of Buffer Operation (Push / Override)
 * 
 * 
 */

void UART_interrupt_receiveToBuffer(UART_interrupt_t ubuf, bool mode);

/**
 * @brief   Creates UART_interrupt container.
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
UART_interrupt_t UART_interrupt_init(void* receiveBuffer, void* transmitBuffer,
                            void (*circularBuffer_overwrite)(void* cbuf, uint8_t data), 
                            int8_t (*circularBuffer_push)(void* cbuf, uint8_t data),
                            int8_t (*circularBuffer_read)(void* cbuf, uint8_t* data) );

/**
 * @brief
 *  If the UDRE_Vect interrupt has been called before the next Element of the Buffer is read
 *  and is written into transmit buffer register
 * @param ubuf
 *  Uart_interrupt handler
 */
void UART_interrupt_transmitFromBuffer(UART_interrupt_t ubuf);

/**
 * @brief
 *  Sets the flag that indicates if the transmit buffer register is ready to be written
 * @param ubuf
 *  Uart_interrupt handler
 * @param status
 *  Status of the flag
 * 
 */
void UART_interrupt_setTransmitFlag(UART_interrupt_t ubuf, bool status);

/**
 * @brief
 *  Checks if the scheduled transmission is completed
 * @param ubuf
 *  Uart_interrupt handler
 * 
 */ 

bool UART_interrupt_isTransmitComplete(UART_interrupt_t ubuf);

/**
 * @brief
 *  Checks if the scheduled reception is completed
 * @param ubuf
 *  Uart_interrupt handler
 * 
 */ 

bool UART_interrupt_isReceiveComplete(UART_interrupt_t ubuf);
/**
 * @brief
 *  Sets the flag that indicates if the receive buffer register is ready to be read
 * @param ubuf
 *  UART_interrupt handler
 * @param status
 *  Status of the flag
 * 
 */ 
void UART_interrupt_setReceiveFlag(UART_interrupt_t ubuf, bool status);


/**
 * @brief
 *  Frees the UART_interrupt handler
 * @param ubuf
 *  UART_interrupt handler
 * 
 * 
 */ 
void UART_interrupt_free(UART_interrupt_t ubuf);

uint8_t getCountRec(UART_interrupt_t ubuf);

#endif