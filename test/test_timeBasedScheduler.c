#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/priorityQueueHeap.h"
#include "bootcamp/interrupt.h"
#include <unity.h>
#include "bootcamp/arduinoArch.h"

#define TASKQUEUELENGTH 15

volatile uint8_t count = 0;
timeBasedScheduler_t specialTBScheduler;
uint16_t currentTime = 0;

void test_timeBasedScheduler_init(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    TEST_ASSERT_TRUE(tBScheduler);
    
    //Always set Pointer to 0 after free
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_addOneTask(void){
        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 1,0));

    TEST_ASSERT_EQUAL_UINT8(1, priorityQueueHeap_peekAt(queue, 0)->priority);
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){
        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);
    for (int i = 0; i < TASKQUEUELENGTH; i++)
    {
        TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, i,0));
    }
    
    TEST_ASSERT_FALSE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 20, 0));
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_addOnePeriodicTask(void){
        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    TEST_ASSERT_TRUE(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0));
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_addOnePeriodicTaskToFull(void){
        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);


    for (size_t i = 0; i <TASKQUEUELENGTH; i++)
    {
        timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0);
    }
    TEST_ASSERT_FALSE(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0));
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void help_timeBasedSchedule(){

    count++;
}

void test_timeBasedScheduler_schedule(void){
        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);


    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150, 0);
    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 254,10,50, 0);
    timeBasedScheduler_markIfReady(tBScheduler);
    timeBasedScheduler_schedule(tBScheduler);
    TEST_ASSERT_EQUAL_UINT8(1,count);
    TEST_ASSERT_EQUAL_UINT8(110,priorityQueueHeap_peekAt(tBScheduler->queue,1)->startTime);
    count = 0;
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_scheduleOnEmpty(void){
        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_schedule(tBScheduler);
    TEST_ASSERT_EQUAL_PTR(NULL, priorityQueueHeap_peekAt(tBScheduler->queue,0));
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;  
}

void test_timeBasedScheduler_scheduleNonPeriodicTask(void){
        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150,0);
    timeBasedScheduler_addTask(tBScheduler,help_timeBasedSchedule, 254,0);
    timeBasedScheduler_markIfReady(tBScheduler);
    timeBasedScheduler_schedule(tBScheduler);
    TEST_ASSERT_EQUAL_UINT8(1,count);
    TEST_ASSERT_EQUAL_PTR(NULL, priorityQueueHeap_peekAt(tBScheduler->queue,1));
    count = 0;
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_markIfReady(void){
    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    task task1;

    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 255,10,50, 0);
    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 0,40,120, 0);
    timeBasedScheduler_markIfReady(tBScheduler);

    task1 = *priorityQueueHeap_getNextReady(tBScheduler->queue);
    TEST_ASSERT_EQUAL_PTR(&test_timeBasedScheduler_addOneTask,task1.functions.voidfunction);

    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void test_timeBasedScheduler_incrementTimer(void){

        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 65530;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    for (size_t i = 0; i < 5; i++)
    {
        timeBasedScheduler_incrementTimer(tBScheduler);
        TEST_ASSERT_FALSE(tBScheduler ->overflow);
        TEST_ASSERT_EQUAL_UINT16(65531+i, currentTime);
    }
    timeBasedScheduler_incrementTimer(tBScheduler);
    TEST_ASSERT_TRUE(tBScheduler->overflow);


    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
    tBScheduler = 0;
}

void addTask(void){

    timeBasedScheduler_addTaskWithParam(specialTBScheduler, &addTask, 44,44,44);

}


void test_timeBasedScheduler_addTaskWithTask(void){

        task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 65530;

    specialTBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_addPeriodicTask(specialTBScheduler,addTask, 255,10,150,0);
    TEST_ASSERT_EQUAL_UINT8(1, priorityQueueHeap_size(queue));
    timeBasedScheduler_markIfReady(specialTBScheduler);
    timeBasedScheduler_schedule(specialTBScheduler);
    TEST_ASSERT_EQUAL_UINT8(2, priorityQueueHeap_size(queue));
    timeBasedScheduler_free(specialTBScheduler);
    specialTBScheduler = NULL;
    free(tQ);
    priorityQueueHeap_free(queue);

}

void test_timeBasedScheduler_addTaskWithTimeOverflow(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 65430;

    specialTBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_addPeriodicTask(specialTBScheduler,addTask, 255,10000,0,0);
    TEST_ASSERT_EQUAL_UINT8(1, priorityQueueHeap_size(queue));
    timeBasedScheduler_markIfReady(specialTBScheduler);
    timeBasedScheduler_schedule(specialTBScheduler);
    TEST_ASSERT_EQUAL_UINT8(2, priorityQueueHeap_size(queue));   

    timeBasedScheduler_free(specialTBScheduler);
    specialTBScheduler = NULL;
    free(tQ);
    priorityQueueHeap_free(queue);
}




void test_timeBasedScheduler_deleteTask(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_addPeriodicTaskWithParam(tBScheduler, 0, 0, 0, 0, 0, 0, 0);
    timeBasedScheduler_deleteTask(tBScheduler, 0);
    TEST_ASSERT_EQUAL_UINT8(0, priorityQueueHeap_size(queue));
    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_getAvailableIdWhenNoneTaken(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);
    
    TEST_ASSERT_EQUAL_UINT8(0, timeBasedScheduler_findNextAvailableId(tBScheduler));
    


    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_getAvailableIdWhenOneTaken(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);
    timeBasedScheduler_findNextAvailableId(tBScheduler);
    TEST_ASSERT_EQUAL_UINT8(1, timeBasedScheduler_findNextAvailableId(tBScheduler));
    


    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_getAvailableIdWhenFirstFreeSecondTaken(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);
    timeBasedScheduler_findNextAvailableId(tBScheduler);
    timeBasedScheduler_findNextAvailableId(tBScheduler);
    timeBasedScheduler_freeID(tBScheduler, 0);
    TEST_ASSERT_EQUAL_UINT8(0, timeBasedScheduler_findNextAvailableId(tBScheduler));
    


    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_getAvailableIdFreeId(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);
    timeBasedScheduler_findNextAvailableId(tBScheduler);
    timeBasedScheduler_freeID(tBScheduler, 0);
    TEST_ASSERT_EQUAL_UINT8(0, timeBasedScheduler_findNextAvailableId(tBScheduler));
    


    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
}

void test_timeBasedScheduler_getUsedIds(void){

    task * tQ = malloc(sizeof(task)*TASKQUEUELENGTH);
    priorityQueueHeap_t queue = priorityQueueHeap_init(TASKQUEUELENGTH,tQ);
    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);
    for (size_t i = 0; i < 32; i++)
    {
        timeBasedScheduler_findNextAvailableId(tBScheduler);
    }
    for (size_t i = 0; i < 32; i++)
    {
        if(i%2 == 0){
            timeBasedScheduler_freeID(tBScheduler, i);
        }
    }
    uint32_t usedIds = timeBasedScheduler_getUsedIDsInt(tBScheduler);

    TEST_ASSERT_EQUAL_UINT8(2863311530, usedIds);
    


    timeBasedScheduler_free(tBScheduler);
    free(tQ);
    priorityQueueHeap_free(queue);
}



//void timeBasedScheduler