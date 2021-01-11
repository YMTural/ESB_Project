#include "build/temp/_test_priorityQueueHeap.c"
#include "libs/bootcamp/interrupt.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/priorityQueueHeap.h"






void test_priorityQueueHeap_init(void){



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    do {if ((queue)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(11)));}} while(0);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_addOne(void){



    task task;

    task.function = test_priorityQueueHeap_addOne;

    task.priority = 255;

    task.isPeriodic = NONPERIODIC;

    task.period = 0;

    task.isReady = 

                  1

                      ;

    task.startTime = 23;



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task))), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT8);

    priorityQueueHeap_free(queue);

}





void test_priorityQueueHeap_getNextOnce(void){



    task task1;

    task1.function = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT8);



    task taskE = *(priorityQueueHeap_getNext(queue));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((taskE.priority)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NONPERIODIC)), (UNITY_INT)(UNITY_UINT8 )((taskE.isPeriodic)), (

   ((void *)0)

   ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((taskE.period)), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_UINT8);

    do {if ((taskE.isReady)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(51)));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((23)), (UNITY_INT)(UNITY_UINT8 )((taskE.startTime)), (

   ((void *)0)

   ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT64)((test_priorityQueueHeap_addOne)), (UNITY_INT64)((taskE.function)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_HEX64);



    priorityQueueHeap_free(queue);

}





void test_priorityQueueHeap_addMultiple(void){



    task task1;

    task1.function = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);

    for (size_t i = 0; i < 32; i++)

    {

        task1.priority = i;

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

       ((void *)0)

       ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_UINT8);

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((priorityQueueHeap_add(queue, task1))), (

   ((void *)0)

   ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT8);





    for (int i = 0; i < 32/2-1; i++){



        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+1)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(80)));}} while(0);

        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+2)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(81)));}} while(0);

    }

    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_swapOnce(void){



    task task1;

    task1.id = 1;

    task1.function = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    priorityQueueHeap_add(queue, task1);

    task1.id = 2;

    task1.priority = 2;

    priorityQueueHeap_add(queue, task1);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_heapify(void){



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    task task1;

    task1.function = test_priorityQueueHeap_addOne;

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

       ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_UINT8);

    }

    priorityQueueHeap_peekAt(queue, 32/8)->priority = 0;

    priorityQueueHeap_heapify(queue, 32/8);



    for (int i = 0; i < 32/2-1; i++)

    {

        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+1)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(130)));}} while(0);

        do {if ((priorityQueueHeap_peekAt(queue,i)->priority > priorityQueueHeap_peekAt(queue,2*i+2)->priority)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(131)));}} while(0);

    }



}



void test_priorityQueueHeap_getMultiple(void){



    task task1;

    task1.id = 0;

    task1.function = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;

    task taskE;

    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    for (size_t i = 0; i < 32; i++)

    {

        task1.id = i;

        task1.priority = 32 -i;

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_add(queue, task1))), (

       ((void *)0)

       ), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_UINT8);

    }



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((priorityQueueHeap_add(queue, task1))), (

   ((void *)0)

   ), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_INT8);



    for(size_t i = 0; i < 32; i++)

    {



        taskE = *(priorityQueueHeap_getNext(queue));



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((taskE.id)), (

       ((void *)0)

       ), (UNITY_UINT)(163), UNITY_DISPLAY_STYLE_UINT8);

    }



    priorityQueueHeap_free(queue);

}

void test_priorityQueueHeap_getFromNone(void){





    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    do {if (!(priorityQueueHeap_getNext(queue))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(173)));}} while(0);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_peekAtNull(void){



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    do {if (!(priorityQueueHeap_peekAt(queue,1))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(182)));}} while(0);

    priorityQueueHeap_free(queue);

}







void test_priorityQueueHeap_getNextReady(void){





    task task1;

    task1.id = 0;

    task1.function = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   0

                        ;

    task1.startTime = 23;

    task taskE;

    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



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

   ), (UNITY_UINT)(214), UNITY_DISPLAY_STYLE_INT8);

    priorityQueueHeap_free(queue);

}

void test_priorityQueueHeap_size(void){



    task task1;

    task1.id = 0;

    task1.function = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   0

                        ;

    task1.startTime = 23;



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);

    for (size_t i = 0; i < 32; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_size(queue))), (

       ((void *)0)

       ), (UNITY_UINT)(231), UNITY_DISPLAY_STYLE_UINT8);

        priorityQueueHeap_add(queue, task1);

    }



    priorityQueueHeap_free(queue);



}

void test_priorityQueueHeap_capacity(void){

    priorityQueueHeap_t queue;



    for (size_t i = 0; i < 32; i++)

    {

        queue = priorityQueueHeap_init(i);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((priorityQueueHeap_capacity(queue))), (

       ((void *)0)

       ), (UNITY_UINT)(244), UNITY_DISPLAY_STYLE_UINT8);

        priorityQueueHeap_free(queue);

    }





}



void test_priorityQueueHeap_getNextReadyFromNull(void){



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);



    do {if (!(priorityQueueHeap_getNextReady(queue))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(255)));}} while(0);



    priorityQueueHeap_free(queue);

}



void test_priorityQueueHeap_getNextReadyFromOne(void){



    task task1;

    task1.id = 0;

    task1.function = test_priorityQueueHeap_addOne;

    task1.priority = 255;

    task1.isPeriodic = NONPERIODIC;

    task1.period = 0;

    task1.isReady = 

                   1

                       ;

    task1.startTime = 23;



    priorityQueueHeap_t queue = priorityQueueHeap_init(32);

    priorityQueueHeap_add(queue,task1);



    do {if ((priorityQueueHeap_getNextReady(queue))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(274)));}} while(0);



    priorityQueueHeap_free(queue);

}
