#include <unity.h>
#include "bootcamp/circularBuffer.h"
#include <math.h>
#define BUFFERSIZE 124
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))



void test_circularBuffer_init(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);


    TEST_ASSERT_TRUE(test_cBuffer);
    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}

void test_circularBuffer_free(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    
    circularBuffer_free(test_cBuffer);
    //Always set Pointer to 0 after free
    test_cBuffer = 0;

    TEST_ASSERT_FALSE(test_cBuffer);

    free(test_buffer);
    circularBuffer_free(test_cBuffer);

}


void test_circularBuffer_reset(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);

    uint8_t* address;

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        address = test_buffer + i;
        *address = i;
    }
    
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    circularBuffer_reset(test_cBuffer);
    
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        address = test_buffer + i;

        TEST_ASSERT_EQUAL_INT8(0,*address);
    }
    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}
void test_circularBuffer_capacity(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);

    TEST_ASSERT_EQUAL_UINT8(BUFFERSIZE, circularBuffer_capacity(test_cBuffer));

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}

void test_circularBuffer_pushFull(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
       TEST_ASSERT_EQUAL_INT8(0,circularBuffer_push(test_cBuffer,i));
    }

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}

void test_circularBuffer_pushOver(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
     for (size_t i = 0; i <BUFFERSIZE+BUFFERSIZE; i++)
    {
        circularBuffer_push(test_cBuffer,i);
    }
    for (size_t i = BUFFERSIZE; i <BUFFERSIZE+BUFFERSIZE; i++)
    {
       TEST_ASSERT_EQUAL_INT8(-1,circularBuffer_push(test_cBuffer,i));
    }


    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}
void test_circularBuffer_pushCheck(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        circularBuffer_push(test_cBuffer,i);
    }
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        TEST_ASSERT_EQUAL_INT8(i,*(test_buffer+i));
    }

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}

void test_circularBuffer_readAll(void){
    char message[1];
    uint8_t data=0;
    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
     circularBuffer_push(test_cBuffer,i);
    }
    
    for (char i = 0; i < BUFFERSIZE; i++)
    {
        message[0] = 48+i; 
        TEST_ASSERT_EQUAL_INT8_MESSAGE(0,circularBuffer_read(test_cBuffer,&data),message);
    }

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}

void test_circularBuffer_readCheck(void){
    char message[1];
    uint8_t data=0;
    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
     circularBuffer_push(test_cBuffer,i);
    }
    
    for (uint8_t i = 0; i < BUFFERSIZE; i++)
    {
        message[0] = 48+ (char) i;

        circularBuffer_read(test_cBuffer,&data);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(i,data,message);
       
    }
    
    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}
void test_circularBuffer_readEmpty(void){
   
    char message[1];

    uint8_t data;

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    
    for (uint8_t i = 0; i < BUFFERSIZE; i++)
    {
        message[0] = 48+ (char) i;

        circularBuffer_read(test_cBuffer,&data);
        TEST_ASSERT_EQUAL_INT8_MESSAGE(-1,circularBuffer_read(test_cBuffer,&data),message);
       
    }
    
    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}


void test_circularBuffer_sizeFillingUp(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
     TEST_ASSERT_EQUAL_UINT8(i, circularBuffer_size(test_cBuffer));   
     circularBuffer_push(test_cBuffer,i);
    }
    
    //TEST_ASSERT_EQUAL_UINT8(0, circularBuffer_size(test_cBuffer));

    free(test_buffer);
    circularBuffer_free(test_cBuffer);

}

void test_circularBuffer_sizeLooping(void){
    char message[1];
    uint8_t data;
    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    
    for (size_t i = 0; i < BUFFERSIZE/2; i++)
    {
     circularBuffer_push(test_cBuffer,i);
    }
    for (size_t i = 0; i < BUFFERSIZE / 4; i++)
    {  
     circularBuffer_read(test_cBuffer,&data);
    }
    for (size_t i = 0; i < BUFFERSIZE+BUFFERSIZE; i++)
    {
    message[0] = 48+ (char) i;
     TEST_ASSERT_EQUAL_UINT8( (BUFFERSIZE / 2) - (BUFFERSIZE / 4) , circularBuffer_size(test_cBuffer) );   
     circularBuffer_push(test_cBuffer,i);
     circularBuffer_read(test_cBuffer,&data);
    }
 

    free(test_buffer);
    circularBuffer_free(test_cBuffer);

}


void test_circularBuffer_fullEmpty(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);

    TEST_ASSERT_FALSE(circularBuffer_full(test_cBuffer));

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}
void test_circularBuffer_fullFull(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
     circularBuffer_push(test_cBuffer,i);
    }

    TEST_ASSERT_TRUE(circularBuffer_full(test_cBuffer));

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}


void test_circularBuffer_empty(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);

    TEST_ASSERT_TRUE(circularBuffer_empty(test_cBuffer));

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}

void test_circularBuffer_overWriteAll(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    uint8_t num;
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
     circularBuffer_push(test_cBuffer,i);
    }
    for (size_t i = 0; i < BUFFERSIZE * 2; i++)
    {
        num = i*i + 10;
        circularBuffer_overwrite(test_cBuffer,num);
        TEST_ASSERT_EQUAL_INT(num, *(test_buffer + (i % BUFFERSIZE) ));
    }

    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}
void test_circularBuffer_overwriteCheckTwice(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    uint8_t data;
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
       circularBuffer_overwrite(test_cBuffer,i);
    }
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        circularBuffer_read(test_cBuffer,&data);
    }
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
       circularBuffer_overwrite(test_cBuffer,i+i);
    }
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        TEST_ASSERT_EQUAL_INT8(i+i,*(test_buffer+i));
    }
    free(test_buffer);
    circularBuffer_free(test_cBuffer);
}
void test_circularBuffer_sizeFullBuffer(void){

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, BUFFERSIZE);
    uint8_t data;
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        circularBuffer_push(test_cBuffer,i);
    }
    TEST_ASSERT_EQUAL_UINT8(BUFFERSIZE, circularBuffer_size(test_cBuffer));


}