#include "bootcamp/priorityQueueHeap.h"
#include <unity.h>
#include "bootcamp/interrupt.h"
#define BUFFERSIZE 32



void test_priorityQueueHeap_init(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);
    
    TEST_ASSERT_TRUE(queue);

    priorityQueueHeap_free(queue);
}

void test_priorityQueueHeap_addOne(void){

    
    task task;
    task.function = test_priorityQueueHeap_addOne;
    task.priority = 255;
    task.isPeriodic = NONPERIODIC;
    task.period = 0;
    task.isReady = true;
    task.startTime = 23;

    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);
    TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_add(queue, task));
}

void test_priorityQueueHeap_getNextOnce(void){

    task task1;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);

    TEST_ASSERT_EQUAL_UINT8(0,priorityQueueHeap_add(queue, task1));

    task taskE = *(priorityQueueHeap_getNext(queue));

    TEST_ASSERT_EQUAL_UINT8(255,taskE.priority);
    TEST_ASSERT_EQUAL_UINT8(NONPERIODIC,taskE.isPeriodic);
    TEST_ASSERT_EQUAL_UINT8(0,taskE.period);
    TEST_ASSERT_TRUE(taskE.isReady);
    TEST_ASSERT_EQUAL_UINT8(23,taskE.startTime);
    TEST_ASSERT_EQUAL_UINT8(test_priorityQueueHeap_addOne,taskE.function);

}

void test_priorityQueue_addMultiple(void){

    
    task task1;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);
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
}

void test_priorityQueueHeap_swapOnce(void){

    task task1;
    task1.id = 1;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;

    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);

    priorityQueueHeap_add(queue, task1);
    task1.id = 2;
    task1.priority = 2;
    priorityQueueHeap_add(queue, task1);


}
/*
void test_priorityQueueHeap_heapify(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);

    task task1;
    task1.function = test_priorityQueueHeap_addOne;
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
    

}

*/

void test_priorityQueueHeap_getMultiple(void){

    task task1;
    task1.id = 0;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;
    task taskE; 
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);

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
    


}
void test_priorityQueueHeap_getFromNone(void){

    task task1;
    task1.id = 0;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;
    task taskE; 
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);

    TEST_ASSERT_FALSE(priorityQueueHeap_getNext(queue));


}

void test_priorityQueue_peekAtNull(void){

    task task1;
    task1.id = 0;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;
    task taskE; 
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);
    
    TEST_ASSERT_FALSE(priorityQueueHeap_peekAt(queue,1));

}



void test_priorityQueue_getNextReady(void){


    task task1;
    task1.id = 0;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = false;
    task1.startTime = 23;
    task taskE; 
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);

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

}



void test_priorityQueue_getNextReadyFromNull(void){

    task task1;
    task1.id = 0;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = false;
    task1.startTime = 23;
    task taskE; 
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);
    TEST_ASSERT_FALSE(priorityQueueHeap_getNextReady(queue));
    


}

void test_priorityQueue_getNextReadyFromOne(void){

    task task1;
    task1.id = 0;
    task1.function = test_priorityQueueHeap_addOne;
    task1.priority = 255;
    task1.isPeriodic = NONPERIODIC;
    task1.period = 0;
    task1.isReady = true;
    task1.startTime = 23;
    task taskE; 
    priorityQueueHeap_t queue = priorityQueueHeap_init(BUFFERSIZE);

    priorityQueueHeap_add(queue,task1);
    TEST_ASSERT_TRUE(priorityQueueHeap_getNextReady(queue));
    


}

