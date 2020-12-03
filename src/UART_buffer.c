#include "bootcamp/UART_buffer.h"

struct UART_buffer {

    //Circularbuffer pointer
    uint8_t* receiveBuffer;   
    uint8_t* transmitBuffer;
    
    //function pointer
    void (*overwrite)(uint8_t* cbuf, uint8_t data);
    bool (*push)(uint8_t* cbuf, uint8_t data);
    int8_t (*read)(uint8_t* cbuf, uint8_t* data);

};

UART_buffer_t UART_buffer_init(uint8_t* receiveBuffer, uint8_t* transmitBuffer,
    void(*circularBuffer_overwrite)(uint8_t* cbuf, uint8_t data), bool (*circularBuffer_push)(uint8_t* cbuf, uint8_t data),
    int8_t(*circularBuffer_read)(uint8_t* cbuf, uint8_t* data)){

        UART_init(MYUBRR);

        UART_buffer_t u_buf = malloc(sizeof(UART_buffer_t));

        u_buf -> receiveBuffer = receiveBuffer;
        u_buf -> transmitBuffer = transmitBuffer;

        u_buf -> overwrite = circularBuffer_overwrite;
        //Push data on receive Buffer
        u_buf -> push = circularBuffer_push;
        //Read data from transmitbuffer
        u_buf -> read = circularBuffer_read;

        return u_buf;
    }

void UART_buffer_free(UART_buffer_t ubuf){

    free(ubuf);
}

void UART_buffer_overwriteReceive(UART_buffer_t ubuf){

    ubuf->overwrite(ubuf -> receiveBuffer,UART_receive());

}

bool UART_buffer_receive(UART_buffer_t ubuf){
    
    bool result = ubuf->push(ubuf -> receiveBuffer, UART_receive());

    return result;
}

int8_t UART_buffer_transmitFromBuffer(UART_buffer_t ubuf){
    uint8_t data;
    if(ubuf->read(ubuf -> transmitBuffer, &data) == -1){
            return -1;
        }
    UART_transmit(data);
    return 0;
}

int8_t UART_buffer_transmitMultipleFromBuffer(UART_buffer_t ubuf, uint8_t count){



    for(uint8_t i = 0; i < count; i++){
        uint8_t data;
        if(ubuf->read(ubuf -> transmitBuffer, &data) == -1){
            return -1;
        }
        UART_transmit(data);
    }
    return 0;
}



