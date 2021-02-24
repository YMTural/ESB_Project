#include "build/temp/_test_circularBuffer.c"
#include "libs/bootcamp/circularBuffer.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"












void test_circularBuffer_init(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);



    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);





    do {if ((test_cBuffer)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(16)));}} while(0);

    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}



void test_circularBuffer_free(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);



    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    circularBuffer_free(test_cBuffer);



    test_cBuffer = 0;



    do {if (!(test_cBuffer)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(31)));}} while(0);



    free(test_buffer);

    circularBuffer_free(test_cBuffer);



}





void test_circularBuffer_reset(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);



    uint8_t* address;



    for (size_t i = 0; i < 4; i++)

    {

        address = test_buffer + i;

        *address = i;

    }



    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);

    circularBuffer_reset(test_cBuffer);



    for (size_t i = 0; i < 4; i++)

    {

        address = test_buffer + i;



        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((*address)), (

       ((void *)0)

       ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT8);

    }

    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}

void test_circularBuffer_capacity(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((4)), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_capacity(test_cBuffer))), (

   ((void *)0)

   ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_UINT8);



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}



void test_circularBuffer_pushFull(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (size_t i = 0; i < 4; i++)

    {

       UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((circularBuffer_push(test_cBuffer,i))), (

      ((void *)0)

      ), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_INT8);

    }



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}



void test_circularBuffer_pushOver(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);

     for (size_t i = 0; i <4 +4; i++)

    {

        circularBuffer_push(test_cBuffer,i);

    }

    for (size_t i = 4; i <4 +4; i++)

    {

       UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((circularBuffer_push(test_cBuffer,i))), (

      ((void *)0)

      ), (UNITY_UINT)(98), UNITY_DISPLAY_STYLE_INT8);

    }





    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}

void test_circularBuffer_pushCheck(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (size_t i = 0; i < 4; i++)

    {

        circularBuffer_push(test_cBuffer,i);

    }

    for (size_t i = 0; i < 4; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((i)), (UNITY_INT)(UNITY_INT8 )((*(test_buffer+i))), (

       ((void *)0)

       ), (UNITY_UINT)(116), UNITY_DISPLAY_STYLE_INT8);

    }



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}



void test_circularBuffer_readAll(void){

    char message[1];

    uint8_t data=0;

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);

    for (size_t i = 0; i < 4; i++)

    {

     circularBuffer_push(test_cBuffer,i);

    }



    for (char i = 0; i < 4; i++)

    {

        message[0] = 48+i;

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((circularBuffer_read(test_cBuffer,&data))), ((message)), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_INT8);

    }



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}



void test_circularBuffer_readCheck(void){

    char message[1];

    uint8_t data=0;

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (size_t i = 0; i < 4; i++)

    {

     circularBuffer_push(test_cBuffer,i);

    }



    for (uint8_t i = 0; i < 4; i++)

    {

        message[0] = 48+ (char) i;



        circularBuffer_read(test_cBuffer,&data);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((data)), ((message)), (UNITY_UINT)(159), UNITY_DISPLAY_STYLE_UINT8);



    }



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}

void test_circularBuffer_readEmpty(void){



    char message[1];



    uint8_t data;



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (uint8_t i = 0; i < 4; i++)

    {

        message[0] = 48+ (char) i;



        circularBuffer_read(test_cBuffer,&data);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((circularBuffer_read(test_cBuffer,&data))), ((message)), (UNITY_UINT)(180), UNITY_DISPLAY_STYLE_INT8);



    }



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}





void test_circularBuffer_sizeFillingUp(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (size_t i = 0; i < 4; i++)

    {

     UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_size(test_cBuffer))), (

    ((void *)0)

    ), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_UINT8);

     circularBuffer_push(test_cBuffer,i);

    }







    free(test_buffer);

    circularBuffer_free(test_cBuffer);



}



void test_circularBuffer_sizeLooping(void){

    char message[1];

    uint8_t data;

    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (size_t i = 0; i < 4/2; i++)

    {

     circularBuffer_push(test_cBuffer,i);

    }

    for (size_t i = 0; i < 4 / 4; i++)

    {

     circularBuffer_read(test_cBuffer,&data);

    }

    for (size_t i = 0; i < 4 +4; i++)

    {

    message[0] = 48+ (char) i;

     UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((4 / 2) - (4 / 4))), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_size(test_cBuffer))), (

    ((void *)0)

    ), (UNITY_UINT)(224), UNITY_DISPLAY_STYLE_UINT8);

     circularBuffer_push(test_cBuffer,i);

     circularBuffer_read(test_cBuffer,&data);

    }





    free(test_buffer);

    circularBuffer_free(test_cBuffer);



}





void test_circularBuffer_fullEmpty(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    do {if (!(circularBuffer_full(test_cBuffer))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(241)));}} while(0);



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}

void test_circularBuffer_fullFull(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (size_t i = 0; i < 4; i++)

    {

     circularBuffer_push(test_cBuffer,i);

    }



    do {if ((circularBuffer_full(test_cBuffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(256)));}} while(0);



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}





void test_circularBuffer_empty(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    do {if ((circularBuffer_empty(test_cBuffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(268)));}} while(0);



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}



void test_circularBuffer_overWriteAll(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);

    uint8_t num;

    for (size_t i = 0; i < 4; i++)

    {

     circularBuffer_push(test_cBuffer,i);

    }

    for (size_t i = 0; i < 4 * 2; i++)

    {

        num = i*i + 10;

        circularBuffer_overwrite(test_cBuffer,num);

        UnityAssertEqualNumber((UNITY_INT)((num)), (UNITY_INT)((*(test_buffer + (i % 4) ))), (

       ((void *)0)

       ), (UNITY_UINT)(287), UNITY_DISPLAY_STYLE_INT);

    }



    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}

void test_circularBuffer_overwriteCheckTwice(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);

    uint8_t data;

    for (size_t i = 0; i < 4; i++)

    {

       circularBuffer_overwrite(test_cBuffer,i);

    }

    for (size_t i = 0; i < 4; i++)

    {

        circularBuffer_read(test_cBuffer,&data);

    }

    for (size_t i = 0; i < 4; i++)

    {

       circularBuffer_overwrite(test_cBuffer,i+i);

    }

    for (size_t i = 0; i < 4; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((i+i)), (UNITY_INT)(UNITY_INT8 )((*(test_buffer+i))), (

       ((void *)0)

       ), (UNITY_UINT)(312), UNITY_DISPLAY_STYLE_INT8);

    }

    free(test_buffer);

    circularBuffer_free(test_cBuffer);

}

void test_circularBuffer_sizeFullBuffer(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);

    uint8_t data;

    for (size_t i = 0; i < 4; i++)

    {

        circularBuffer_push(test_cBuffer,i);

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((4)), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_size(test_cBuffer))), (

   ((void *)0)

   ), (UNITY_UINT)(326), UNITY_DISPLAY_STYLE_UINT8);





}



void test_circularBuffer_mostRecentElement2Elements(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    circularBuffer_push(test_cBuffer, 120);

    circularBuffer_push(test_cBuffer, 232);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((232)), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_mostRecentElement(test_cBuffer))), (

   ((void *)0)

   ), (UNITY_UINT)(338), UNITY_DISPLAY_STYLE_UINT8);





    circularBuffer_free(test_cBuffer);

    free(test_buffer);

}



void test_circularBuffer_mostRecentElementPushFullThenOverrride(void){



    uint8_t* test_buffer = malloc(sizeof(uint8_t)*4);

    circularBuffer_t test_cBuffer = circularBuffer_init(test_buffer, 4);



    for (uint8_t i = 0; i < 4; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_size(test_cBuffer))), (

       ((void *)0)

       ), (UNITY_UINT)(352), UNITY_DISPLAY_STYLE_UINT8);

        do {if (!(circularBuffer_push(test_cBuffer, i+10))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(353)));}} while(0);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i+10)), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_mostRecentElement(test_cBuffer))), (

       ((void *)0)

       ), (UNITY_UINT)(354), UNITY_DISPLAY_STYLE_UINT8);

    }

        uint8_t data;

    for (uint8_t i = 0; i < 4; i++)

    {

        circularBuffer_read(test_cBuffer, &data);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i+10)), (UNITY_INT)(UNITY_UINT8 )((data)), (

       ((void *)0)

       ), (UNITY_UINT)(360), UNITY_DISPLAY_STYLE_UINT8);

    }

    for (uint8_t i = 0; i < 4; i++)

    {

        circularBuffer_overwrite(test_cBuffer, i);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((circularBuffer_mostRecentElement(test_cBuffer))), (

       ((void *)0)

       ), (UNITY_UINT)(365), UNITY_DISPLAY_STYLE_UINT8);

    }

    circularBuffer_free(test_cBuffer);

    free(test_buffer);

}
