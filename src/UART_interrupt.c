#include "bootcamp/UART_interrupt.h"


volatile uint8_t UART_interrupt_tCounter = 10;
volatile uint8_t UART_interrupt_rCounter = 10;

volatile uint8_t UART_interrupt_data;

volatile uint8_t* UART_interrupt_receiveBuffer;   

volatile uint8_t* UART_interrupt_transmitBuffer;

struct UART_interrupt_buffer {

    //Circularbuffer pointer
    uint8_t* receiveBuffer;   
    uint8_t* transmitBuffer;
    
    //function pointer
    void (*overwrite)(uint8_t* cbuf, uint8_t data);
    bool (*push)(uint8_t* cbuf, uint8_t data);
    int8_t (*read)(uint8_t* cbuf, uint8_t* data);

};

void UART_interrupt_init(uint8_t* receiveBuffer, uint8_t* transmitBuffer){

    UART_interrupt_receiveBuffer = receiveBuffer;
    UART_interrupt_transmitBuffer = transmitBuffer;

}



void UART_interrupt_transmitFromBuffer(circularBuffer_t transmitBuffer, uint8_t count){
    UART_flush();
    UART_interrupt_tCounter = count;
    UART_enableTransmitInterrupt();
}


uint8_t UART_interrupt_receiveToBuffer(circularBuffer_t receiveBuffer, uint8_t count){
    UART_flush();
    UART_interrupt_rCounter = count;
    UART_enableReceiveInterrupt();

}

ISR(USART_UDRE_vect){

    cli();
    if(!circularBuffer_read(UART_interrupt_transmitBuffer, &UART_interrupt_data)){
    UART_overwriteRegister(UART_interrupt_data);
    }
    UART_interrupt_tCounter--;
    UART_disableTransmitInterrupt();
    sei();
}

ISR(USART_TX_vect){
  cli();
  if(!UART_interrupt_tCounter){

    UART_disableTransmitCompleteInterrupt();
  }else{

    UART_enableTransmitInterrupt();
  }
  sei();
}

ISR(USART_RX_vect){
  
  cli();
  if(!UART_interrupt_rCounter){
    UART_interrupt_data = UDR0;  
    circularBuffer_overwrite(UART_interrupt_receiveBuffer, UART_interrupt_data);
    UART_interrupt_rCounter--;
  }else{
    UART_disableReceiveInterrupt();
  }
  sei();
}