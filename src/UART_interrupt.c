#include "bootcamp/UART_interrupt.h"

struct UART_interrupt {

    //Circularbuffer pointer
    uint8_t* receiveBuffer;   
    uint8_t* transmitBuffer;
    
    //function pointer
    void (*overwrite)(void* cbuf, uint8_t data);
    int8_t (*push)(void* cbuf, uint8_t data);
    int8_t (*read)(void* cbuf, uint8_t* data);

    uint8_t transmitCounter;

    uint8_t receiveCounter;

    bool dataIsPresent;

    bool readyForTransmit;
};

UART_interrupt_t UART_interrupt_init(void* receiveBuffer, void* transmitBuffer,
                            void (*circularBuffer_overwrite)(void* cbuf, uint8_t data), 
                            int8_t (*circularBuffer_push)(void* cbuf, uint8_t data),
                            int8_t (*circularBuffer_read)(void* cbuf, uint8_t* data) ){

    UART_init(MYUBRR);                        

    UART_interrupt_t u_buf = malloc(sizeof(UART_interrupt));

    u_buf -> receiveBuffer = (uint8_t*) receiveBuffer;
    u_buf -> transmitBuffer = (uint8_t*) transmitBuffer;

    //Overwrite data on the receive Buffer
    u_buf -> overwrite = circularBuffer_overwrite;
    //Push data on receive Buffer
    u_buf -> push = circularBuffer_push;
    //Read data from transmitbuffer
    u_buf -> read = circularBuffer_read;

    u_buf -> transmitCounter = 0;
    u_buf -> receiveCounter = 0;

    u_buf -> dataIsPresent = false;
    u_buf -> readyForTransmit = false;

    return u_buf;
}

void UART_interrupt_free(UART_interrupt_t ubuf){

    free(ubuf);
}

void UART_interrupt_setTransmitFlag(UART_interrupt_t ubuf, bool status){

   ubuf -> readyForTransmit = status;
}

bool UART_interrupt_isTransmitComplete(UART_interrupt_t ubuf){

    return (ubuf -> transmitCounter) == 0;
}

bool UART_interrupt_isReceiveComplete(UART_interrupt_t ubuf){

    return (ubuf -> receiveCounter) == 0;
}

void UART_interrupt_setReceiveFlag(UART_interrupt_t ubuf, bool status){

    ubuf -> dataIsPresent = status;
}

void UART_interrupt_transmitFromBufferInit(UART_interrupt_t ubuf, uint8_t count){
    UART_flush();
    if(count > 0){
      ubuf -> transmitCounter += count;
      UART_enableTransmitInterrupt();
    }
}

uint8_t getCountRec(UART_interrupt_t ubuf){


  return ubuf->receiveCounter;
}

void UART_interrupt_transmitFromBuffer(UART_interrupt_t ubuf){

    uint8_t data;
    if(ubuf -> readyForTransmit){
      UART_flush();
      UART_enableTransmitCompleteInterrupt();

      if(!ubuf -> read(ubuf -> transmitBuffer, &data)){
        UART_overwriteRegister(data);
        ubuf -> transmitCounter--;
        ubuf -> readyForTransmit = false;
    }
  }
}

void UART_interrupt_receiveToBufferInit(UART_interrupt_t ubuf, uint8_t count){
    UART_flush();
    if(count > 0){
      ubuf -> receiveCounter = count;
      UART_enableReceiveInterrupt();
    }
}

void UART_interrupt_receiveToBuffer(UART_interrupt_t ubuf, bool mode){

    if(ubuf -> dataIsPresent){
      uint8_t data = UART_forceReadData();
      //UART_transmit(data);
      if(mode){
       ubuf -> overwrite(ubuf -> receiveBuffer, data);
        ubuf -> receiveCounter--;
      }  
      else{
       ubuf -> push(ubuf -> receiveBuffer, data);
       ubuf -> receiveCounter--;
      }
      ubuf -> dataIsPresent = false;
      if(UART_interrupt_isReceiveComplete(ubuf)){
        UART_disableReceiveInterrupt();
        }else{
          UART_enableReceiveInterrupt();
        }
    }
}


//Zugehörige ISR

/*
ISR(USART_UDRE_vect){

  cli();
  UART_interrupt_setTransmitFlag(uBuf, true);
  UART_disableTransmitInterrupt();
  sei();
}

ISR(USART_TX_vect){

  cli();
  if(UART_interrupt_isTransmitComplete(uBuf)){

    UART_disableTransmitCompleteInterrupt();
  }
  else{
    UART_disableTransmitCompleteInterrupt();
    UART_enableTransmitInterrupt();
  }
  sei();
}

ISR(USART_RX_vect){

  cli();
    UART_disableReceiveInterrupt();
    UART_interrupt_setReceiveFlag(uBuf, true); 
  sei();
}
*/