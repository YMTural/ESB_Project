#include "bootcamp/UART.h"

void UART_init(unsigned int ubrr){

    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /*Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (3<<UCSZ00);
    
}

void UART_transmit(unsigned char data){

    /* Wait for empty transmit buffer */
    while (!(UCSRnA & (1<<UDREn)));

    /* Put data into buffer, sends the data */
    UDRn = data;

}

unsigned char UART_Receive(void){

    /* Wait for data to be received */
    while (!(UCSRnA & (1<<RXCn)));

    /* Get and return received data from buffer */
    return UDRn;
    
    }