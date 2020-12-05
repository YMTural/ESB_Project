#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/interrupt.h"
#include <unity.h>

#define TASKQUEUELENGTH 15


void test_timeBasedScheduler_init(void){

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH);
    TEST_ASSERT_TRUE(tBScheduler);
    
    //Always set Pointer to 0 after free
    timeBasedScheduler_free(tBScheduler);
    tBScheduler = 0;


}

void test_timeBasedScheduler_addOneTask(void){

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH);

    TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 1));

}

void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH);
    for (int i = 0; i < TASKQUEUELENGTH; i++)
    {
        TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, i));
    }
    
    TEST_ASSERT_FALSE(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 20));
}



void test_timeBasedScheduler_addOnePeriodicTask(void){

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH);

    task task1;
    task1.id = 0;
    task1.function = test_timeBasedScheduler_addOneTask;
    task1.priority = 255;
    task1.isPeriodic = PERIODIC;
    task1.period = 10;
    task1.isReady = true;
    task1.startTime = 23;

    TEST_ASSERT_TRUE(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23));

}
void test_timeBasedScheduler_addOnePeriodicTaskToFull(void){

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH);

    task task1;
    task1.id = 0;
    task1.function = test_timeBasedScheduler_addOneTask;
    task1.priority = 255;
    task1.isPeriodic = PERIODIC;
    task1.period = 10;
    task1.isReady = true;
    task1.startTime = 23;

    for (size_t i = 0; i <TASKQUEUELENGTH; i++)
    {
        timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23);
    }
    TEST_ASSERT_FALSE(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23));

}


void test_timeBasedScheduler_schedule(void){



    
}




/*
void test_timeBasedScheduler_markIfReady(void){

    uint16_t currentTime = 100;

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(TASKQUEUELENGTH);

    task task1;

    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 255,10,50);
    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 0,40,120);
    timeBasedScheduler_markIfReady(tBScheduler, currentTime);

    //task1 = *priorityQueueHeap_getNextReady(tBScheduler);
    TEST_ASSERT_TRUE(task1.function);


}*/