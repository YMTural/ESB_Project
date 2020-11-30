#ifndef UART_H
#define UART_H

#include <stdint.h>
//#include "bootcamp/mock_avr.h"
#include <avr/io.h>
#include "bootcamp/circularBuffer.h"

#define FOSC 1600000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



/**
 * @brief   Initializes UART protocol.
 *          Using Polling, fixed frame of 8
 *          Data, 1 start and 1 stop bit.
 *          Requiring receive and transmit buffer 
 * 
 * @param   ubrr
 *  Baud Rate Register Value
 */
void UART_init(unsigned int ubrr);


/**
 * @brief   A data transmission is initiated by
 *          loading the transmit register with data
 *          from the buffer which is to be transmitted.
 *           
 * @param   data
 *  8 bit data which is to be transmitted
 */
void UART_transmit(circularBuffer_t cbuf, void (*readBuffer)(circularBuffer_t, uint8_t*));

/**
 * @brief   A data transmission is initiated by
 *          loading the transmit register with data
 *          from the buffer. All data in the buffer will be transmitted
 *           
 * @param   data
 *  8 bit data which is to be transmitted
 */
void UART_transmitN(circularBuffer_t cbuf, void (*readBuffer)(circularBuffer_t, uint8_t*), uint8_t count);
/**
 * @brief   The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted from the register
 *          into the buffer. 0 on success, -1 if failed           
 */
short UART_receive(circularBuffer_t cbuf, short (*pushBuffer)(circularBuffer_t));

/**
 * @brief   The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted from the register
 *          into the buffer overwriting old data if necessary.       
 */
void UART_overwriteReceive(circularBuffer_t cbuf, void (*overwriteBuffer)(circularBuffer_t));

/**
 * @brief   The receiver registerbuffer FIFO will be flushed when
 *          the receiver is disabled and unread data will
 *          be lost        
 */
void UART_flush(void);


#endif