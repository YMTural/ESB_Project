#ifndef UART_H
#define UART_H

#include <avr/io.h>
#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


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
 *          loading the transmit buffer with the
 *          data to be transmitted.
 *           
 * @param   data
 *  8 bit data which is to be transmitted
 */
void UART_transmit(unsigned char data);

/**
 * @brief   The receiver starts data reception when
 *          it detects a valid start bit and stops when
 *          the first stop bit of a frame is received.
 *          The data will be shifted from the register
 *          into the buffer.            
 */
unsigned char UART_receive(void);

/**
 * @brief   The receiver registerbuffer FIFO will be flushed when
 *          the receiver is disabled and unread data will
 *          be lost        
 */
void UART_flush(void);


#endif