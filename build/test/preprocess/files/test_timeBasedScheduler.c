#include "build/temp/_test_timeBasedScheduler.c"
#include "libs/bootcamp/arduinoArch.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/interrupt.h"
#include "libs/bootcamp/priorityQueueHeap.h"
#include "libs/bootcamp/timeBasedScheduler.h"










volatile uint8_t count = 0;

timeBasedScheduler_t specialTBScheduler;



void test_timeBasedScheduler_init(void){



    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init( 15, queue, priorityQueueHeap_size,

                                                                priorityQueueHeap_capacity, priorityQueueHeap_add,

                                                                priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    do {if ((tBScheduler)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(19)));}} while(0);





    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_addOneTask(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 1,0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(31)));}} while(0);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(queue, 0)->priority)), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);

    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);

    for (int i = 0; i < 15; i++)

    {

        do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, i,0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(43)));}} while(0);

    }



    do {if (!(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 20, 0))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(46)));}} while(0);

    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_addOnePeriodicTask(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    do {if ((timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(55)));}} while(0);

    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_addOnePeriodicTaskToFull(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);





    for (size_t i = 0; i <15; i++)

    {

        timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0);

    }

    do {if (!(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(69)));}} while(0);

    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void help_timeBasedSchedule(){



    count++;

}



void test_timeBasedScheduler_schedule(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);





    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150, 0);

    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 254,10,50, 0);

    timeBasedScheduler_markIfReady(tBScheduler, currentTime);

    timeBasedScheduler_schedule(tBScheduler,&currentTime);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((count)), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((110)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(tBScheduler->queue,1)->startTime)), (

   ((void *)0)

   ), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_UINT8);

    count = 0;

    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_scheduleOnEmpty(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    timeBasedScheduler_schedule(tBScheduler,&currentTime);

    UnityAssertEqualNumber((UNITY_INT64)((

   ((void *)0)

   )), (UNITY_INT64)((priorityQueueHeap_peekAt(tBScheduler->queue,0))), (

   ((void *)0)

   ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_HEX64);

    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_scheduleNonPeriodicTask(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150,0);

    timeBasedScheduler_addTask(tBScheduler,help_timeBasedSchedule, 254,0);

    timeBasedScheduler_markIfReady(tBScheduler, currentTime);

    timeBasedScheduler_schedule(tBScheduler,&currentTime);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((count)), (

   ((void *)0)

   ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT64)((

   ((void *)0)

   )), (UNITY_INT64)((priorityQueueHeap_peekAt(tBScheduler->queue,1))), (

   ((void *)0)

   ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_HEX64);

    count = 0;

    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_markIfReady(void){

    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    task task1;



    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 255,10,50, 0);

    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 0,40,120, 0);

    timeBasedScheduler_markIfReady(tBScheduler, currentTime);



    task1 = *priorityQueueHeap_getNextReady(tBScheduler->queue);

    UnityAssertEqualNumber((UNITY_INT64)((&test_timeBasedScheduler_addOneTask)), (UNITY_INT64)((task1.function)), (

   ((void *)0)

   ), (UNITY_UINT)(139), UNITY_DISPLAY_STYLE_HEX64);



    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_incrementTimer(void){



    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    uint16_t currentTime = 65530;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    for (size_t i = 0; i < 5; i++)

    {

        timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);

        do {if (!(tBScheduler ->overflow)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(155)));}} while(0);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((65531+i)), (UNITY_INT)(UNITY_UINT16)((currentTime)), (

       ((void *)0)

       ), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_UINT16);

    }

    timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);

    do {if ((tBScheduler->overflow)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(159)));}} while(0);





    timeBasedScheduler_free(tBScheduler);

    priorityQueueHeap_free(queue);

}



void addTask(void){



    timeBasedScheduler_addTask(specialTBScheduler, &addTask, 44,44);



}





void timeBasedScheduler_addTaskWithTask(void){



    priorityQueueHeap_t queue = priorityQueueHeap_init(15);

    uint16_t currentTime = 65530;



    specialTBScheduler = timeBasedScheduler_init(15, queue, priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady);



    timeBasedScheduler_addPeriodicTask(specialTBScheduler,addTask, 255,10,150,0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_UINT8);

    timeBasedScheduler_markIfReady(specialTBScheduler, currentTime);

    timeBasedScheduler_schedule(specialTBScheduler,&currentTime);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(184), UNITY_DISPLAY_STYLE_UINT8);





}
