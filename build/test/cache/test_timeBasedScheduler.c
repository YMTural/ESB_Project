#include "build/temp/_test_timeBasedScheduler.c"
#include "libs/bootcamp/arduinoArch.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/interrupt.h"
#include "libs/bootcamp/priorityQueueHeap.h"
#include "libs/bootcamp/timeBasedScheduler.h"










volatile uint8_t count = 0;

timeBasedScheduler_t specialTBScheduler;

uint16_t currentTime = 0;



void test_timeBasedScheduler_init(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    do {if ((tBScheduler)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(19)));}} while(0);





    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_addOneTask(void){

        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 1,0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(33)));}} while(0);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(queue, 0)->priority)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT8);

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){

        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    for (int i = 0; i < 15; i++)

    {

        do {if ((timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, i,0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(48)));}} while(0);

    }



    do {if (!(timeBasedScheduler_addTask(tBScheduler, timeBasedScheduler_addTask, 20, 0))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(51)));}} while(0);

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_addOnePeriodicTask(void){

        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    do {if ((timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(63)));}} while(0);

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_addOnePeriodicTaskToFull(void){

        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);





    for (size_t i = 0; i <15; i++)

    {

        timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0);

    }

    do {if (!(timeBasedScheduler_addPeriodicTask(tBScheduler, test_timeBasedScheduler_addOneTask, 255,10,23,0))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(80)));}} while(0);

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void help_timeBasedSchedule(){



    count++;

}



void test_timeBasedScheduler_schedule(void){

        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);





    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150, 0);

    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 254,10,50, 0);

    timeBasedScheduler_markIfReady(tBScheduler);

    timeBasedScheduler_schedule(tBScheduler);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((count)), (

   ((void *)0)

   ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((110)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(tBScheduler->queue,1)->startTime)), (

   ((void *)0)

   ), (UNITY_UINT)(105), UNITY_DISPLAY_STYLE_UINT8);

    count = 0;

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_scheduleOnEmpty(void){

        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    timeBasedScheduler_schedule(tBScheduler);

    UnityAssertEqualNumber((UNITY_INT64)((

   ((void *)0)

   )), (UNITY_INT64)((priorityQueueHeap_peekAt(tBScheduler->queue,0))), (

   ((void *)0)

   ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_HEX64);

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_scheduleNonPeriodicTask(void){

        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    timeBasedScheduler_addPeriodicTask(tBScheduler,help_timeBasedSchedule, 255,10,150,0);

    timeBasedScheduler_addTask(tBScheduler,help_timeBasedSchedule, 254,0);

    timeBasedScheduler_markIfReady(tBScheduler);

    timeBasedScheduler_schedule(tBScheduler);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((count)), (

   ((void *)0)

   ), (UNITY_UINT)(139), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT64)((

   ((void *)0)

   )), (UNITY_INT64)((priorityQueueHeap_peekAt(tBScheduler->queue,1))), (

   ((void *)0)

   ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_HEX64);

    count = 0;

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_markIfReady(void){

    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    task task1;



    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 255,10,50, 0);

    timeBasedScheduler_addPeriodicTask(tBScheduler,test_timeBasedScheduler_addOneTask, 0,40,120, 0);

    timeBasedScheduler_markIfReady(tBScheduler);



    task1 = *priorityQueueHeap_getNextReady(tBScheduler->queue);

    UnityAssertEqualNumber((UNITY_INT64)((&test_timeBasedScheduler_addOneTask)), (UNITY_INT64)((task1.functions.voidfunction)), (

   ((void *)0)

   ), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_HEX64);



    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void test_timeBasedScheduler_incrementTimer(void){



        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 65530;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    for (size_t i = 0; i < 5; i++)

    {

        timeBasedScheduler_incrementTimer(tBScheduler);

        do {if (!(tBScheduler ->overflow)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(181)));}} while(0);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((65531+i)), (UNITY_INT)(UNITY_UINT16)((currentTime)), (

       ((void *)0)

       ), (UNITY_UINT)(182), UNITY_DISPLAY_STYLE_UINT16);

    }

    timeBasedScheduler_incrementTimer(tBScheduler);

    do {if ((tBScheduler->overflow)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(185)));}} while(0);





    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

    tBScheduler = 0;

}



void addTask(void){



    timeBasedScheduler_addTaskWithParam(specialTBScheduler, &addTask, 44,44,44);



}





void test_timeBasedScheduler_addTaskWithTask(void){



        task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 65530;



    specialTBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    timeBasedScheduler_addPeriodicTask(specialTBScheduler,addTask, 255,10,150,0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(210), UNITY_DISPLAY_STYLE_UINT8);

    timeBasedScheduler_markIfReady(specialTBScheduler);

    timeBasedScheduler_schedule(specialTBScheduler);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(213), UNITY_DISPLAY_STYLE_UINT8);

    timeBasedScheduler_free(specialTBScheduler);

    specialTBScheduler = 

                        ((void *)0)

                            ;

    free(tQ);

    priorityQueueHeap_free(queue);



}



void test_timeBasedScheduler_addTaskWithTimeOverflow(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 65430;



    specialTBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    timeBasedScheduler_addPeriodicTask(specialTBScheduler,addTask, 255,10000,0,0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(230), UNITY_DISPLAY_STYLE_UINT8);

    timeBasedScheduler_markIfReady(specialTBScheduler);

    timeBasedScheduler_schedule(specialTBScheduler);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(233), UNITY_DISPLAY_STYLE_UINT8);



    timeBasedScheduler_free(specialTBScheduler);

    specialTBScheduler = 

                        ((void *)0)

                            ;

    free(tQ);

    priorityQueueHeap_free(queue);

}









void test_timeBasedScheduler_deleteTask(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    timeBasedScheduler_addPeriodicTaskWithParam(tBScheduler, 0, 0, 0, 0, 0, 0, 0);

    timeBasedScheduler_deleteTask(tBScheduler, 0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(254), UNITY_DISPLAY_STYLE_UINT8);

    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_getAvailableIdWhenNoneTaken(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((timeBasedScheduler_findNextAvailableId(tBScheduler))), (

   ((void *)0)

   ), (UNITY_UINT)(268), UNITY_DISPLAY_STYLE_UINT8);







    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_getAvailableIdWhenOneTaken(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_findNextAvailableId(tBScheduler);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((timeBasedScheduler_findNextAvailableId(tBScheduler))), (

   ((void *)0)

   ), (UNITY_UINT)(285), UNITY_DISPLAY_STYLE_UINT8);







    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_getAvailableIdWhenFirstFreeSecondTaken(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_findNextAvailableId(tBScheduler);

    timeBasedScheduler_findNextAvailableId(tBScheduler);

    timeBasedScheduler_freeID(tBScheduler, 0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((timeBasedScheduler_findNextAvailableId(tBScheduler))), (

   ((void *)0)

   ), (UNITY_UINT)(304), UNITY_DISPLAY_STYLE_UINT8);







    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_getAvailableIdFreeId(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

    uint16_t currentTime = 100;



    timeBasedScheduler_t tBScheduler = timeBasedScheduler_init(&currentTime, queue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

    timeBasedScheduler_findNextAvailableId(tBScheduler);

    timeBasedScheduler_freeID(tBScheduler, 0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((timeBasedScheduler_findNextAvailableId(tBScheduler))), (

   ((void *)0)

   ), (UNITY_UINT)(322), UNITY_DISPLAY_STYLE_UINT8);







    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

}



void test_timeBasedScheduler_getUsedIds(void){



    task * tQ = malloc(sizeof(task)*15);

    priorityQueueHeap_t queue = priorityQueueHeap_init(15,tQ);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2863311530)), (UNITY_INT)(UNITY_UINT8 )((usedIds)), (

   ((void *)0)

   ), (UNITY_UINT)(350), UNITY_DISPLAY_STYLE_UINT8);







    timeBasedScheduler_free(tBScheduler);

    free(tQ);

    priorityQueueHeap_free(queue);

}
