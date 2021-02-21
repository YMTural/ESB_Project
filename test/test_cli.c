#include <unity.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//For debbuging
#include "bootcamp/UART.h"
//
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART_interrupt.h"
#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/adc_temperature.h"
#include "bootcamp/priorityQueueHeap.h"

#define BUFFERSIZE 10

void test_generalTest(void){

    uint16_t t;


    task* taskArray = malloc(sizeof(task)*35);

    uint8_t* transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    uint8_t* recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
    priorityQueueHeap_t pQueue = priorityQueueHeap_init(35, taskArray);
    circularBuffer_t cTransmitbuffer = circularBuffer_init(transBuffer, BUFFERSIZE);
    
    circularBuffer_t cReceivebuffer = circularBuffer_init(recBuffer, BUFFERSIZE);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&t, pQueue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    UART_interrupt_t uBuf = UART_interrupt_init(cReceivebuffer, cTransmitbuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

    timeBasedScheduler_schedule(tBScheduler);
    UART_interrupt_receiveToBufferInit(uBuf,1);

    
    printf("Hello World!");
}