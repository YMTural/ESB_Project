#include "build/temp/_test_priorityQueueHeap.c"
#include "libs/bootcamp/interrupt.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/priorityQueueHeap.h"








void test_priorityQueueHeap_init(void){



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    do {if ((queue)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(12)));}} while(0);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_addOne(void){



    task task1;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);

    priorityQueueHeap_free(queue);

}





void test_priorityQueueHeap_getNextOnce(void){



    task task1;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

   ((void *)0)

   ), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_UINT8);



    task taskE = *(priorityQueueHeap_getNext(queue));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((taskE.priority)), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NONPERIODIC)), (UNITY_INT)(UNITY_UINT8 )((taskE.isPeriodic)), (

   ((void *)0)

   ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((taskE.period)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_UINT8);

    do {if ((taskE.isReady)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(54)));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((23)), (UNITY_INT)(UNITY_UINT8 )((taskE.startTime)), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT64)((test_priorityQueueHeap_addOne)), (UNITY_INT64)((taskE.functions.voidfunction)), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_HEX64);



    priorityQueueHeap_free(queue);

}





void test_priorityQueueHeap_addMultiple(void){



    task task1;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);

    for (size_t i = 0; i < 32; i++)

    {

        task1.priority = i;

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

       ((void *)0)

       ), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_UINT8);

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((priorityQueueHeap_add(queue, task1))), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT8);





    for (int i = 0; i < 32/2-1; i++){



        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+1)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(84)));}} while(0);

        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+2)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(85)));}} while(0);

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

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    priorityQueueHeap_add(queue, task1);

    task1.id = 2;

    task1.priority = 2;

    priorityQueueHeap_add(queue, task1);

    priorityQueueHeap_swap(0, 1, queue);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((2)), (UNITY_INT)(UNITY_INT8 )((priorityQueueHeap_peekAt(queue, 0) -> id)), (

   ((void *)0)

   ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((1)), (UNITY_INT)(UNITY_INT8 )((priorityQueueHeap_peekAt(queue, 1) -> id)), (

   ((void *)0)

   ), (UNITY_UINT)(110), UNITY_DISPLAY_STYLE_INT8);

    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_heapify(void){



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    task task1;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    for (size_t i = 0; i < 32; i++)

    {

        task1.id = i;

        task1.priority = i;

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

       ((void *)0)

       ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_UINT8);

    }

    priorityQueueHeap_peekAt(queue, 32/8)->priority = 0;

    priorityQueueHeap_heapify(queue, 32/8);



    for (int i = 0; i < 32/2-1; i++)

    {

        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+1)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(138)));}} while(0);

        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+2)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(139)));}} while(0);

    }



}



void test_priorityQueueHeap_getMultiple(void){



    task task1;

    task1.id = 0;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;

    task taskE;

    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    for (size_t i = 0; i < 32; i++)

    {

        task1.id = i;

        task1.priority = 32 -i;

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

       ((void *)0)

       ), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_UINT8);

    }



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((priorityQueueHeap_add(queue, task1))), (

   ((void *)0)

   ), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_INT8);



    for(size_t i = 0; i < 32; i++)

    {



        taskE = *(priorityQueueHeap_getNext(queue));



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((taskE.id)), (

       ((void *)0)

       ), (UNITY_UINT)(172), UNITY_DISPLAY_STYLE_UINT8);

    }



    priorityQueueHeap_free(queue);

}

void test_priorityQueueHeap_getFromNone(void){





    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    do {if (!(priorityQueueHeap_getNext(queue))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(183)));}} while(0);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_peekAtNull(void){



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    do {if (!(priorityQueueHeap_peekAt(queue,1))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(193)));}} while(0);

    priorityQueueHeap_free(queue);

}







void test_priorityQueueHeap_getNextReady(void){





    task task1;

    task1.id = 0;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   0

                        ;

    task1.startTime = 23;

    task taskE;

    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    priorityQueueHeap_add(queue,task1);

    task1.id++;

    task1.priority = 240;

    task1.isReady = 

                   1

                       ;

    priorityQueueHeap_add(queue,task1);

    task1.id++;

    task1.priority++;

    priorityQueueHeap_add(queue,task1);

    task1.id++;

    task1.priority++;

    priorityQueueHeap_add(queue,task1);

    taskE = *priorityQueueHeap_getNextReady(queue);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((3)), (UNITY_INT)(UNITY_INT8 )((taskE.id)), (

   ((void *)0)

   ), (UNITY_UINT)(226), UNITY_DISPLAY_STYLE_INT8);

    priorityQueueHeap_free(queue);

}

void test_priorityQueueHeap_size(void){



    task task1;

    task1.id = 0;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   0

                        ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);

    for (size_t i = 0; i < 32; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

       ((void *)0)

       ), (UNITY_UINT)(244), UNITY_DISPLAY_STYLE_UINT8);

        priorityQueueHeap_add(queue, task1);

    }



    priorityQueueHeap_free(queue);



}

void test_priorityQueueHeap_capacity(void){

    priorityQueueHeap_t queue;



    for (size_t i = 0; i < 32; i++)

    {

        task * tQ = malloc(sizeof(task)*32);

        queue = priorityQueueHeap_init(i,tQ);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_capacity(queue))), (

       ((void *)0)

       ), (UNITY_UINT)(258), UNITY_DISPLAY_STYLE_UINT8);

        priorityQueueHeap_free(queue);

    }





}



void test_priorityQueueHeap_getNextReadyFromNull(void){



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    do {if (!(priorityQueueHeap_getNextReady(queue))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(270)));}} while(0);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_getNextReadyFromOne(void){



    task task1;

    task1.id = 0;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);

    priorityQueueHeap_add(queue,task1);



    do {if ((priorityQueueHeap_getNextReady(queue))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(290)));}} while(0);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_deleteOneItem(void){



    task task1;

    task1.id = 0;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);

    priorityQueueHeap_add(queue,task1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(309), UNITY_DISPLAY_STYLE_UINT8);

    priorityQueueHeap_deleteItem(queue,0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(311), UNITY_DISPLAY_STYLE_UINT8);

    free(queue);

}



void test_priorityQueueHeap_deleteFromMiddle(void){



    task task1;

    task1.id = 0;

    task1.functions.voidfunction = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);

    priorityQueueHeap_add(queue,task1);

    task1.id = 1;

    task1.priority = 254;

    priorityQueueHeap_add(queue,task1);

    task1.id = 2;

    task1.priority = 253;

    priorityQueueHeap_add(queue,task1);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((3)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(336), UNITY_DISPLAY_STYLE_UINT8);

    priorityQueueHeap_deleteItem(queue, 1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(338), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(queue,1) -> id)), (

   ((void *)0)

   ), (UNITY_UINT)(339), UNITY_DISPLAY_STYLE_UINT8);

}



void test_priorityQueueHeap_deleteFromNone(void){



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);

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

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;

    priorityQueueHeap_add(pQueue, task1);

}





void test_priorityQueueHeap_heapAttributeInSchedule(void){



    task * tQ = malloc(sizeof(task)*32);

    priorityQueueHeap_t queue = priorityQueueHeap_init(32, tQ);



    task task1;

    task1.id = 0;

    task1.functions.charfunction = addTaskToQueue;

    task1.priority = 144;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;

    task1.param = queue;

    priorityQueueHeap_add(queue, task1);

    priorityQueueHeap_add(queue, task1);

    task testTask = *priorityQueueHeap_getNextReady(queue);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(382), UNITY_DISPLAY_STYLE_UINT8);

    testTask.functions.charfunction(testTask.param);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

   ((void *)0)

   ), (UNITY_UINT)(384), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_peekAt(queue,0)->priority)), (

   ((void *)0)

   ), (UNITY_UINT)(385), UNITY_DISPLAY_STYLE_UINT8);

    free(tQ);

    priorityQueueHeap_free(queue);



}
