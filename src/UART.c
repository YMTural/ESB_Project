#include "bootcamp/UART.h"

void UART_init(unsigned int ubrr){

    //Set baud rate 9600
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    //Enable receiver and transmitter 
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    //Set frame format: 8data, 1stop bit
    UCSR0C = (3<<UCSZ00);
}

void UART_interruptInit(unsigned int ubrr){

    //Set baud rate 9600
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    //Enable receiver and transmitter 
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    //Set frame format: 8data, 1stop bit
    UCSR0C = (3<<UCSZ00);
}

void UART_transmit(uint8_t data){

    //Wait for empty transmit register
    while (!(UCSR0A & (1<<UDRE0)));

    //Put data into register, sends the data
    UDR0 = data;
}

void UART_overwriteRegister(uint8_t data){

    UDR0 = data;
}

uint8_t UART_forceReadData(void){

    return UDR0;
}

uint8_t UART_receive(){

    //Wait for data to be received 
    while (!(UCSR0A & (1<<RXC0)));
    //Get and return received data to buffer
    return UDR0;
}

void UART_flush(void){

    unsigned char dummy;
    while (UCSR0A & (1<<RXC0)) dummy = UDR0;
}

void UART_enableTransmitInterrupt(void){

    UCSR0B = UCSR0B | (1 << UDRIE0);
}

void UART_disableTransmitInterrupt(void){

    UCSR0B &=  ~(1 << UDRIE0);
}

void UART_enableTransmitCompleteInterrupt(void){

    UCSR0B = UCSR0B | (1 << TXCIE0);
}

void UART_disableTransmitCompleteInterrupt(void){

    UCSR0B &= ~(1 << TXCIE0);
}

void UART_enableReceiveInterrupt(void){

    UCSR0B = UCSR0B | (1 << RXCIE0);

}

void UART_disableReceiveInterrupt(void){

    UCSR0B &= ~(1 << RXCIE0);
}