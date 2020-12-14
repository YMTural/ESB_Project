#include "bootcamp/UART_interrupt.h"

//global variables

volatile uint8_t UART_interrupt_tCounter = 0;
volatile uint8_t UART_interrupt_rCounter = 0;

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
    UART_interrupt_tCounter = 0;
    UART_interrupt_rCounter = 0;

}



void UART_interrupt_transmitFromBuffer(uint8_t count){
    UART_flush();
    UART_interrupt_tCounter = count;
    UART_enableTransmitInterrupt();
}


uint8_t UART_interrupt_receiveToBuffer(uint8_t count){
    UART_flush();
    UART_interrupt_rCounter = count;
    UART_enableReceiveInterrupt();

}
#if INCLUDEISR == 1
ISR(USART_UDRE_vect){

    cli();
    UART_enableTransmitCompleteInterrupt();
    if(!circularBuffer_read(UART_interrupt_transmitBuffer, &UART_interrupt_data)){
      UART_overwriteRegister(UART_interrupt_data);
      UART_interrupt_tCounter--;
    }
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
  if(UART_interrupt_rCounter){
    UART_interrupt_data = UDR0;  
    circularBuffer_overwrite(UART_interrupt_receiveBuffer, UART_interrupt_data);
    UART_interrupt_rCounter--;
  }else{
    UART_disableReceiveInterrupt();
  }
  sei();
}
#endif