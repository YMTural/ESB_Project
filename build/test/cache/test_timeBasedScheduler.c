#include "build/temp/_test_timeBasedScheduler.c"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/interrupt.h"
#include "libs/bootcamp/timeBasedScheduler.h"










void test_timeBasedScheduler_init(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);

    do {if ((tBScheduler)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(11)));}} while(0);





    timeBasedScheduler_free(tBScheduler);

    tBScheduler = 0;





}



void test_timeBasedScheduler_addOneTask(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);



    do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 1))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(24)));}} while(0);



}



void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);

    for (int i = 0; i < 15; i++)

    {

        do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, i))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(33)));}} while(0);

    }



    do {if (!(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 20))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(36)));}} while(0);

}







void test_timeBasedScheduler_addOnePeriodicTask(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);



    task task1;

    task1.id = 0;

    task1.function = test_timeBasedScheduler_addOneTask;

    task1.priority = 255;

    task1.isPeriodic = PERIODIC;

    task1.period = 10;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    do {if ((timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(54)));}} while(0);



}

void test_timeBasedScheduler_addOnePeriodicTaskToFull(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);



    task task1;

    task1.id = 0;

    task1.function = test_timeBasedScheduler_addOneTask;

    task1.priority = 255;

    task1.isPeriodic = PERIODIC;

    task1.period = 10;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    for (size_t i = 0; i <15; i++)

    {

        timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23);

    }

    do {if (!(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(74)));}} while(0);



}



void test_timeBasedScheduler_markIfReady(void){



    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);



    task task1;



    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 255,10,50);

    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 0,40,120);

    timeBasedScheduler_markIfReady(tBScheduler, currentTime);





    do {if ((task1.function)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(91)));}} while(0);





}
