#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/priorityQueueHeap.h"
#include "bootcamp/interrupt.h"
#include <unity.h>
#include "bootcamp/arduinoArch.h"

#define TASKQUEUELENGTH 15

volatile uint8_t count = 0;
timeBasedScheduler_t specialTBScheduler;

void test_timeBasedScheduler_init(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init( TASKQUEUELENGTH, queue, priorityQueueHeap_size,
                                                                priorityQueueHeap_capacity, priorityQueueHeap_add,
                                                                priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    TEST_ASSERT_TRUE(tBScheduler);
    
    //Always set Pointer to 0 after free
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_addOneTask(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 1,0));

    TEST_ASSERT_EQUAL_UINT8(1, priorityQueueHeap_peekAt(queue, 0)->priority);
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);
    for (int i = 0; i < TASKQUEUELENGTH; i++)
    {
        TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, i,0));
    }
    
    TEST_ASSERT_FALSE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 20, 0));
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);  
}

void test_timeBasedScheduler_addOnePeriodicTask(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    TEST_ASSERT_TRUE(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0));
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_addOnePeriodicTaskToFull(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);


    for (size_t i = 0; i <TASKQUEUELENGTH; i++)
    {
        timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0);
    }
    TEST_ASSERT_FALSE(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0));
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
}

void help_timeBasedSchedule(){

    count++;
}

void test_timeBasedScheduler_schedule(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);


    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150, 0);
    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 254,10,50, 0);
    timeBasedScheduler_markIfReady(tBScheduler, currentTime);
    timeBasedScheduler_schedule(tBScheduler,&currentTime);
    TEST_ASSERT_EQUAL_UINT8(1,count);
    TEST_ASSERT_EQUAL_UINT8(110,priorityQueueHeap_peekAt(tBScheduler->queue,1)->startTime);
    count = 0;
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_scheduleOnEmpty(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_schedule(tBScheduler,&currentTime);
    TEST_ASSERT_EQUAL_PTR(NULL, priorityQueueHeap_peekAt(tBScheduler->queue,0));
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);    
}

void test_timeBasedScheduler_scheduleNonPeriodicTask(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150,0);
    timeBasedScheduler_addTask(tBScheduler,help_timeBasedSchedule, 254,0);
    timeBasedScheduler_markIfReady(tBScheduler, currentTime);
    timeBasedScheduler_schedule(tBScheduler,&currentTime);
    TEST_ASSERT_EQUAL_UINT8(1,count);
    TEST_ASSERT_EQUAL_PTR(NULL, priorityQueueHeap_peekAt(tBScheduler->queue,1));
    count = 0;
    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_markIfReady(void){
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    task task1;

    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 255,10,50, 0);
    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 0,40,120, 0);
    timeBasedScheduler_markIfReady(tBScheduler, currentTime);

    task1 = *priorityQueueHeap_getNextReady(tBScheduler->queue);
    TEST_ASSERT_EQUAL_PTR(&test_timeBasedScheduler_addOneTask,task1.functions.voidfunction);

    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_incrementTimer(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    uint16_t currentTime = 65530;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    for (size_t i = 0; i < 5; i++)
    {
        timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);
        TEST_ASSERT_FALSE(tBScheduler ->overflow);
        TEST_ASSERT_EQUAL_UINT16(65531+i, currentTime);
    }
    timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);
    TEST_ASSERT_TRUE(tBScheduler->overflow);


    timeBasedScheduler_free(tBScheduler);
    priorityQueueHeap_free(queue);
}

void addTask(void){

    timeBasedScheduler_addTask(specialTBScheduler, &addTask, 44,44);

}


void timeBasedScheduler_addTaskWithTask(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    uint16_t currentTime = 65530;

    specialTBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_addPeriodicTask(specialTBScheduler,addTask, 255,10,150,0);
    TEST_ASSERT_EQUAL_UINT8(1, priorityQueueHeap_size(queue));
    timeBasedScheduler_markIfReady(specialTBScheduler, currentTime);
    timeBasedScheduler_schedule(specialTBScheduler,&currentTime);
    TEST_ASSERT_EQUAL_UINT8(2, priorityQueueHeap_size(queue));
    specialTBScheduler = NULL;
    
}

void timeBasedScheduler_addTaskWithTimeOverflow(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH); 
    uint16_t currentTime = 65430;

    specialTBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_addPeriodicTask(specialTBScheduler,addTask, 255,10000,0,0);
    TEST_ASSERT_EQUAL_UINT8(1, priorityQueueHeap_size(queue));
    timeBasedScheduler_markIfReady(specialTBScheduler, currentTime);
    timeBasedScheduler_schedule(specialTBScheduler, &currentTime);
    TEST_ASSERT_EQUAL_UINT8(2, priorityQueueHeap_size(queue));   


}