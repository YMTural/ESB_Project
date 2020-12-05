#include <unity.h>
#include "bootcamp/UART_buffer.h"
#include "bootcamp/circularBuffer.h"
#include "bootcamp/io.h"
#include "bootcamp/UART.h"
#define BUFFERSIZE 10
#define RUNS 100


void test_UART_buffer_init(void){

    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

    TEST_ASSERT_TRUE(uBuf);
    /*
    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);*/

}
//WTF is going on here?? 2 copies of the same function, but I cant free test_tBuffer in one of them
void test_UART_buffer_receiveOne(void){
    
    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for receive
    UCSR0A = 128;
    UDR0 = 10;
    int8_t data;
    int8_t code = UART_buffer_receive(uBuf);
    TEST_ASSERT_EQUAL_INT8(0,code);
    circularBuffer_read(test_cRBuffer,&data);
    TEST_ASSERT_EQUAL_UINT8(10, data); 

    
    free(test_rBuffer);
    //free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);

}
void test_UART_buffer_receiveOneFF(void){
    
    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for receive
    UCSR0A = 128;
    UDR0 = 10;
    int8_t data;
    int8_t code = UART_buffer_receive(uBuf);
    TEST_ASSERT_EQUAL_INT8(0,code);
    circularBuffer_read(test_cRBuffer,&data);
    TEST_ASSERT_EQUAL_UINT8(10, data); 

    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);


}



void test_UART_buffer_receiveMultiple(void){

    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for receive
    UCSR0A = 128;
    uint8_t data;
    int8_t code;
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        UDR0 = i;
        code = UART_buffer_receive(uBuf);
        TEST_ASSERT_EQUAL_INT8(0,code);
    }

    code = UART_buffer_receive(uBuf);
    TEST_ASSERT_EQUAL_INT8(-1,code);

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        circularBuffer_read(test_cRBuffer,&data);
        TEST_ASSERT_EQUAL_UINT8(i, data); 
    }
 
    /*
    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);*/




}


void test_UART_buffer_overwrite(void){


    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for receive
    UCSR0A = 128;
    uint8_t data;
    int8_t code;

 for (size_t i = 0; i < BUFFERSIZE+BUFFERSIZE; i++)
    {
        UDR0 = i;
        UART_buffer_overwriteReceive(uBuf);
    }

    for (size_t i = BUFFERSIZE; i < BUFFERSIZE+BUFFERSIZE; i++)
    {
        circularBuffer_read(test_cRBuffer,&data);
        TEST_ASSERT_EQUAL_UINT8(i, data); 
    }

    /*
    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);*/

}

void test_UART_buffer_transmitOne(void){

    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for transmit
    UCSR0A = 32;
    int8_t code;

    code = circularBuffer_push(test_cTBuffer,10);
    TEST_ASSERT_EQUAL_INT8(0,code);
    UART_buffer_transmitFromBuffer(uBuf);
    TEST_ASSERT_EQUAL_UINT8(10,UDR0);

    /*
    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);*/
}

void test_UART_buffer_transmitMultiple(void){

    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for transmit
    UCSR0A = 32;

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        circularBuffer_push(test_cTBuffer,i);
        
    }
    TEST_ASSERT_EQUAL_INT8(0,UART_buffer_transmitMultipleFromBuffer(uBuf,BUFFERSIZE));

    /*
    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);*/

}
void test_UART_buffer_transmitFromEmpty(void){

    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for transmit
    UCSR0A = 32;
    int8_t code;

    
    TEST_ASSERT_EQUAL_INT8(-1,UART_buffer_transmitFromBuffer(uBuf));
    /*
    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);*/

}

void test_UART_buffer_transmitMultipleFromEmpty(void){

    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, BUFFERSIZE);
    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, BUFFERSIZE);

    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
    //Set register for transmit
    UCSR0A = 32;
    int8_t code;

    
    TEST_ASSERT_EQUAL_INT8(-1,UART_buffer_transmitMultipleFromBuffer(uBuf,10));

    
    free(test_rBuffer);
    free(test_tBuffer);
    circularBuffer_free(test_cTBuffer);
    circularBuffer_free(test_cRBuffer);
    UART_buffer_free(uBuf);

}