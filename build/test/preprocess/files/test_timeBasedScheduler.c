#include "build/temp/_test_timeBasedScheduler.c"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/timeBasedScheduler.h"








void test_timeBasedScheduler_init(void){



    timeBasedScheduler_t tBSchdeuler = timeBasedScheduler_init(15);

    do {if ((tBSchdeuler)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(10)));}} while(0);





    timeBasedScheduler_free(tBSchdeuler);

    tBSchdeuler = 0;





}



void test_timeBasedScheduler_addOneTask(void){



    timeBasedScheduler_t tBSchdeuler = timeBasedScheduler_init(15);



    do {if ((timeBasedScheduler_addTask(tBSchdeuler, timeBasedScheduler_addTask, 1 , PERIODIC))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(23)));}} while(0);



}



void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void){



    timeBasedScheduler_t tBSchdeuler = timeBasedScheduler_init(15);

    for (int i = 0; i < 15; i++)

    {

        do {if ((timeBasedScheduler_addTask(tBSchdeuler, timeBasedScheduler_addTask, i , PERIODIC))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(32)));}} while(0);

    }



    do {if (!(timeBasedScheduler_addTask(tBSchdeuler, timeBasedScheduler_addTask, 20 , PERIODIC))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(35)));}} while(0);

}
