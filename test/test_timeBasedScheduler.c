#include "bootcamp/timeBasedScheduler.h"
#include <unity.h>

#define TASKQUEUELENGTH 15


void test_timeBasedScheduler_init(void){

    timeBasedScheduler_t tBSchdeuler = timeBasedScheduler_init(TASKQUEUELENGTH);
    TEST_ASSERT_TRUE(tBSchdeuler);
    
    //Always set Pointer to 0 after free
    timeBasedScheduler_free(tBSchdeuler);
    tBSchdeuler = 0;


}

void test_timeBasedScheduler_addOneTask(void){

    timeBasedScheduler_t tBSchdeuler = timeBasedScheduler_init(TASKQUEUELENGTH);

    TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBSchdeuler, timeBasedScheduler_addTask, 1 , PERIODIC));

}

void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){

    timeBasedScheduler_t tBSchdeuler = timeBasedScheduler_init(TASKQUEUELENGTH);
    for (int i = 0; i < TASKQUEUELENGTH; i++)
    {
        TEST_ASSERT_TRUE(timeBasedScheduler_addTask(tBSchdeuler, timeBasedScheduler_addTask, i , PERIODIC));
    }
    
    TEST_ASSERT_FALSE(timeBasedScheduler_addTask(tBSchdeuler, timeBasedScheduler_addTask, 20 , PERIODIC));
}


