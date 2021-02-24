#include "bootcamp/priorityQueueHeap.h"
#include <unity.h>
#include "bootcamp/interrupt.h"
#define BUFFERSIZE 32


void test_priorityQueueHeap_init(void){

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    
    TEST_ASSERT_TRUE(queue);

    priorityQueueHeap_free(queue);
}

void test_priorityQueueHeap_addOne(void){

    task task1;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_add(queue, task1));
    priorityQueueHeap_free(queue);
}


void test_priorityQueueHeap_getNextOnce(void){

    task task1;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);

    TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_add(queue, task1));

    task taskE = *(priorityQueueHeap_getNext(queue));

    TEST_ASSERT_EQUAL_UINT8(255,taskE.priority);
    TEST_ASSERT_EQUAL_UINT8(NONPERIODIC,taskE.isPeriodic);
    TEST_ASSERT_EQUAL_UINT8(0,taskE.period);
    TEST_ASSERT_TRUE(taskE.isReady);
    TEST_ASSERT_EQUAL_UINT8(23,taskE.startTime);
    TEST_ASSERT_EQUAL_PTR(test_priorityQueueHeap_addOne,taskE.functions.voidfunction);

    priorityQueueHeap_free(queue);
}


void test_priorityQueueHeap_addMultiple(void){

    task task1;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        task1.priority = i;
        TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_add(queue, task1));
    }
    TEST_ASSERT_EQUAL_INT8(-1,priorityQueueHeap_add(queue, task1));

    
    for (int i = 0; i < BUFFERSIZE/2-1; i++){

        TEST_ASSERT_TRUE(priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+1)->priority );
        TEST_ASSERT_TRUE(priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+2)->priority );
    }
    priorityQueueHeap_free(queue);
}

void test_priorityQueueHeap_swapOnce(void){

    task task1;
    task1.id = 1;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);

    priorityQueueHeap_add(queue, task1);
    task1.id = 2;
    task1.priority = 2;
    priorityQueueHeap_add(queue, task1);
    priorityQueueHeap_swap(0, 1, queue);
    TEST_ASSERT_EQUAL_INT8(2, priorityQueueHeap_peekAt(queue, 0) -> id);
    TEST_ASSERT_EQUAL_INT8(1, priorityQueueHeap_peekAt(queue, 1) -> id);
    priorityQueueHeap_free(queue);
}

void test_priorityQueueHeap_heapify(void){

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);

    task task1;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        task1.id = i;
        task1.priority = i;
        TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_add(queue, task1));
    }
    priorityQueueHeap_peekAt(queue, BUFFERSIZE/8)->priority = 0;
    priorityQueueHeap_heapify(queue, BUFFERSIZE/8);

    for (int i = 0; i < BUFFERSIZE/2-1; i++)
    {
        TEST_ASSERT_TRUE(priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+1)->priority );
        TEST_ASSERT_TRUE(priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+2)->priority );
    }

}

void test_priorityQueueHeap_getMultiple(void){

    task task1;
    task1.id = 0;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;
    task taskE; 
    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        task1.id = i;
        task1.priority = BUFFERSIZE-i;
        TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_add(queue, task1));
    }

    TEST_ASSERT_EQUAL_INT8(-1,priorityQueueHeap_add(queue, task1));
    
    for(size_t i = 0; i < BUFFERSIZE; i++)
    {

        taskE = *(priorityQueueHeap_getNext(queue));

        TEST_ASSERT_EQUAL_UINT8(i,taskE.id);
    }

    priorityQueueHeap_free(queue);
}
void test_priorityQueueHeap_getFromNone(void){


    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);

    TEST_ASSERT_FALSE(priorityQueueHeap_getNext(queue));

    priorityQueueHeap_free(queue);
}

void test_priorityQueueHeap_peekAtNull(void){

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    
    TEST_ASSERT_FALSE(priorityQueueHeap_peekAt(queue,1));
    priorityQueueHeap_free(queue);
}



void test_priorityQueueHeap_getNextReady(void){


    task task1;
    task1.id = 0;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = false;
    task1.startTime = 23;
    task taskE; 
    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);

    priorityQueueHeap_add(queue,task1);
    task1.id++;
    task1.priority = 240;
    task1.isReady = true;
    priorityQueueHeap_add(queue,task1);
    task1.id++;
    task1.priority++;
    priorityQueueHeap_add(queue,task1);
    task1.id++;
    task1.priority++;
    priorityQueueHeap_add(queue,task1);
    taskE = *priorityQueueHeap_getNextReady(queue);
    TEST_ASSERT_EQUAL_INT8(3,taskE.id);
    priorityQueueHeap_free(queue);
}
void test_priorityQueueHeap_size(void){

    task task1;
    task1.id = 0;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = false;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(i, priorityQueueHeap_size(queue));
        priorityQueueHeap_add(queue, task1);
    }

    priorityQueueHeap_free(queue);

}
void test_priorityQueueHeap_capacity(void){
    priorityQueueHeap_t queue;

    for (size_t i = 0; i < BUFFERSIZE; i++)
    {
        task * tQ = malloc(sizeof(task)*BUFFERSIZE);
        queue = priorityQueueHeap_init(i,tQ);
        TEST_ASSERT_EQUAL_UINT8(i, priorityQueueHeap_capacity(queue));
        priorityQueueHeap_free(queue);
    }
    

}

void test_priorityQueueHeap_getNextReadyFromNull(void){

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    
    TEST_ASSERT_FALSE(priorityQueueHeap_getNextReady(queue));
    
    priorityQueueHeap_free(queue);
}

void test_priorityQueueHeap_getNextReadyFromOne(void){

    task task1;
    task1.id = 0;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    priorityQueueHeap_add(queue,task1);

    TEST_ASSERT_TRUE(priorityQueueHeap_getNextReady(queue));

    priorityQueueHeap_free(queue);
}

void test_priorityQueueHeap_deleteOneItem(void){

    task task1;
    task1.id = 0;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    priorityQueueHeap_add(queue,task1);
    TEST_ASSERT_EQUAL_UINT8(1,priorityQueueHeap_size(queue));
    priorityQueueHeap_deleteItem(queue,0);
    TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_size(queue));
    free(queue);
}

void test_priorityQueueHeap_deleteFromMiddle(void){

    task task1;
    task1.id = 0;
    task1.functions.voidfunction = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    priorityQueueHeap_add(queue,task1);
    task1.id = 1;
    task1.priority = 254;
    priorityQueueHeap_add(queue,task1);
    task1.id = 2;
    task1.priority = 253;
    priorityQueueHeap_add(queue,task1);

    TEST_ASSERT_EQUAL_UINT8(3,priorityQueueHeap_size(queue));
    priorityQueueHeap_deleteItem(queue, 1);
    TEST_ASSERT_EQUAL_UINT8(2,priorityQueueHeap_size(queue));
    TEST_ASSERT_EQUAL_UINT8(2,priorityQueueHeap_peekAt(queue,1) -> id);
}

void test_priorityQueueHeap_deleteFromNone(void){

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);
    priorityQueueHeap_deleteItem(queue, 10);
    priorityQueueHeap_free(queue);
    free(tQ);

}

void addTaskToQueue(char* pQueue){
    task task1;
    task1.id = 55;
    task1.functions.charfunction = addTaskToQueue;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;
    priorityQueueHeap_add(pQueue, task1);
}


void test_priorityQueueHeap_heapAttributeInSchedule(void){

    task * tQ = malloc(sizeof(task)*BUFFERSIZE);
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE, tQ);

    task task1;
    task1.id = 0;
    task1.functions.charfunction = addTaskToQueue;
    task1.priority = 144;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;
    task1.param = queue;
    priorityQueueHeap_add(queue, task1);
    priorityQueueHeap_add(queue, task1);
    task testTask = *priorityQueueHeap_getNextReady(queue);
    TEST_ASSERT_EQUAL_UINT8(1, priorityQueueHeap_size(queue));
    testTask.functions.charfunction(testTask.param);
    TEST_ASSERT_EQUAL_UINT8(2, priorityQueueHeap_size(queue));
    TEST_ASSERT_EQUAL_UINT8(255, priorityQueueHeap_peekAt(queue,0)->priority);
    free(tQ);
    priorityQueueHeap_free(queue);

}
