#include "bootcamp/UART_buffer.h"

struct UART_buffer {

    //Circularbuffer pointer
    uint8_t* receiveBuffer;   
    uint8_t* transmitBuffer;
    
    //function pointer
    void (*overwrite)(void* cbuf, uint8_t data);
    int8_t (*push)(void* cbuf, uint8_t data);
    int8_t (*read)(void* cbuf, uint8_t* data);

};

UART_buffer_t UART_buffer_init(void* receiveBuffer, void* transmitBuffer,
    void(*circularBuffer_overwrite)(void* cbuf, uint8_t data),
    int8_t (*circularBuffer_push)(void* cbuf, uint8_t data),
    int8_t(*circularBuffer_read)(void* cbuf, uint8_t* data)){

        UART_init(MYUBRR);

        UART_buffer_t u_buf = malloc(sizeof(UART_buffer));

        u_buf -> receiveBuffer = (uint8_t*) receiveBuffer;
        u_buf -> transmitBuffer = (uint8_t*) transmitBuffer;

        //Overwrite data on the receive Buffer
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

int8_t UART_buffer_receive(UART_buffer_t ubuf){

    uint8_t data = UART_receive();
    int8_t result = ubuf -> push(ubuf -> receiveBuffer, data);
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



