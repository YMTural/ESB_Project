#include "bootcamp/UART_lib.h"


struct UART_lib
{
    union opType
    {
        UART_buffer_t uPollingBuff;
        UART_interrupt_t uInterruptBuff;
    }opType;
    uint8_t mode;
    uint8_t transmitInit;
    uint8_t receiveInit;
};

UART_lib_t UART_lib_init(uint8_t mode, void* receiveBuffer, void* transmitBuffer,
    void(*circularBuffer_overwrite)(void* cbuf, uint8_t data),
    int8_t (*circularBuffer_push)(void* cbuf, uint8_t data),
    int8_t(*circularBuffer_read)(void* cbuf, uint8_t* data)){

    UART_lib_t ubuf = malloc(sizeof(UART_lib_t));
    switch (mode)
    {
    case POLLINGBUFFER:
    
        ubuf -> opType.uPollingBuff = UART_buffer_init(receiveBuffer, transmitBuffer,
                             circularBuffer_overwrite, 
                             circularBuffer_push,
                             circularBuffer_read);

        break;
    case INTERRUPTBUFFER:
        ubuf -> opType.uInterruptBuff = UART_interrupt_init(receiveBuffer, transmitBuffer,
                             circularBuffer_overwrite, 
                             circularBuffer_push,
                             circularBuffer_read);
        break;
    }
    ubuf -> mode = mode;
    ubuf -> transmitInit = false;
    ubuf -> receiveInit = false;
    return ubuf;
    }
void UART_lib_free(UART_lib_t ubuf){

    UART_buffer_free(ubuf->opType.uPollingBuff);
    UART_interrupt_free(ubuf->opType.uInterruptBuff);
    free(ubuf);
}
void UART_lib_transmit(UART_lib_t ubuf, uint8_t count){

    if(ubuf->mode == POLLINGBUFFER){
        UART_buffer_transmitMultipleFromBuffer(ubuf->opType.uPollingBuff, count);
    }
    else{
        if(ubuf->transmitInit){
            UART_interrupt_transmitFromBuffer(ubuf->opType.uInterruptBuff);
            ubuf->transmitInit = UART_interrupt_isTransmitComplete(ubuf->opType.uInterruptBuff) ? false : true;

        }else
        {
            UART_interrupt_transmitFromBufferInit(ubuf->opType.uInterruptBuff, count);
            ubuf->transmitInit = true;
        }
    }
}

void UART_lib_receive(UART_lib_t ubuf, uint16_t count, uint8_t receiveMode){
    if(ubuf->mode == POLLINGBUFFER){
        if(receiveMode == OVERWRITE){
            
            for(uint16_t i = 0; i < count; i++){
                UART_buffer_overwriteReceive(ubuf->opType.uPollingBuff);
            }
        }else
        {
            for(uint16_t i = 0; i < count; i++){
                UART_transmit(UART_buffer_receive(ubuf->opType.uPollingBuff));
            }
        }
    }
    else{
        if(ubuf->receiveInit){
            UART_interrupt_receiveToBuffer(ubuf->opType.uInterruptBuff, receiveMode);
            ubuf->transmitInit = UART_interrupt_isReceiveComplete(ubuf->opType.uInterruptBuff) ? false : true;

        }else
        {
            UART_interrupt_receiveToBufferInit(ubuf->opType.uInterruptBuff, count);
            ubuf->receiveInit = true;
        }
    }
}

void UART_lib_setTransmitFlag(UART_lib_t ubuf){

   UART_interrupt_setTransmitFlag(ubuf->opType.uInterruptBuff, true);

}


uint8_t UART_lib_isTransmitComplete(UART_lib_t ubuf){

    return UART_interrupt_isTransmitComplete(ubuf->opType.uInterruptBuff);

}

uint8_t UART_lib_isReceiveComplete(UART_lib_t ubuf){

    return UART_interrupt_isReceiveComplete(ubuf->opType.uInterruptBuff);

}

void UART_lib_setReceiveFlag(UART_lib_t ubuf){

    UART_interrupt_setReceiveFlag(ubuf->opType.uInterruptBuff, true);

}

