#include "build/temp/_test_timeBasedScheduler.c"
#include "libs/bootcamp/arduinoArch.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/interrupt.h"
#include "libs/bootcamp/priorityQueueHeap.h"
#include "libs/bootcamp/timeBasedScheduler.h"












volatile uint8_t count = 0;





void test_timeBasedScheduler_init(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);

    do {if ((tBScheduler)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(15)));}} while(0);





    timeBasedScheduler_free(tBScheduler);

    tBScheduler = 0;





}



void test_timeBasedScheduler_addOneTask(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);



    do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 1))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(28)));}} while(0);



}



void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);

    for (int i = 0; i < 15; i++)

    {

        do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, i))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(37)));}} while(0);

    }



    do {if (!(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 20))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(40)));}} while(0);

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



    do {if ((timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(58)));}} while(0);



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

    do {if (!(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(78)));}} while(0);



}



void help_timeBasedSchedule(){



    count++;

}



void test_timeBasedScheduler_schedule(void){



    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);





    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150);

    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 254,10,50);

    timeBasedScheduler_markIfReady(tBScheduler, currentTime);

    timeBasedScheduler_schedule(tBScheduler,&currentTime);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((count)), (

   ((void *)0)

   ), (UNITY_UINT)(98), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((110)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(tBScheduler->queue,1)->startTime)), (

   ((void *)0)

   ), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_UINT8);

    count = 0;

}

void test_timeBasedScheduler_scheduleOnEmpty(void){



    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);







    timeBasedScheduler_schedule(tBScheduler,&currentTime);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((

   ((void *)0)

   )), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(tBScheduler->queue,0))), (

   ((void *)0)

   ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_UINT8);

}





void test_timeBasedScheduler_scheduleNonPeriodicTask(void){



    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);





    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150);

    timeBasedScheduler_addTask(tBScheduler,help_timeBasedSchedule, 254);

    timeBasedScheduler_markIfReady(tBScheduler, currentTime);

    timeBasedScheduler_schedule(tBScheduler,&currentTime);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((count)), (

   ((void *)0)

   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((

   ((void *)0)

   )), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(tBScheduler->queue,1))), (

   ((void *)0)

   ), (UNITY_UINT)(127), UNITY_DISPLAY_STYLE_UINT8);

    count = 0;

}











void test_timeBasedScheduler_markIfReady(void){



    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(15);



    task task1;



    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 255,10,50);

    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 0,40,120);

    timeBasedScheduler_markIfReady(tBScheduler, currentTime);



    task1 = *priorityQueueHeap_getNextReady(tBScheduler->queue);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((&test_timeBasedScheduler_addOneTask)), (UNITY_INT)(UNITY_UINT8 )((task1.function)), (

   ((void *)0)

   ), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_UINT8);





}
