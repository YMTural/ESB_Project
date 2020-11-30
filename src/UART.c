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

void UART_transmit(circularBuffer_t cbuf, void (*readBuffer)(circularBuffer_t, uint8_t*), uint8_t* data){
    
    //Read data from buffer
    (*readBuffer)(cbuf, data);

    //Wait for empty transmit register
    while (!(UCSR0A & (1<<UDRE0)));

    //Put data into register, sends the data
    UDR0 = data;

}

void UART_transmitN(circularBuffer_t cbuf,void (*readBuffer)(circularBuffer_t, uint8_t*), uint8_t count){

    for(int i = 0; i < count; i++){

        uint8_t data;
        (*readBuffer)(cbuf, &data);

        //Wait for empty transmit register
        while (!(UCSR0A & (1<<UDRE0)));

        //Put data into register, sends the data
        UDR0 = data;
    }


}
void UART_overwriteReceive(circularBuffer_t cbuf, void (*overwriteBuffer)(circularBuffer_t)){


    //Wait for data to be received 
    while (!(UCSR0A & (1<<RXC0)));
    
    //Get and return received data to buffer
    (*overwriteBuffer)(cbuf);
}

short UART_Receive(circularBuffer_t cbuf, short (*pushBuffer)(circularBuffer_t)){


    //Wait for data to be received 
    while (!(UCSR0A & (1<<RXC0)));
    //Get and return received data to buffer
    return (*pushBuffer)(cbuf);
   
}
