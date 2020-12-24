#include "build/temp/_test_UART_buffer.c"
#include "libs/bootcamp/UART.h"
#include "libs/bootcamp/io.h"
#include "libs/bootcamp/circularBuffer.h"
#include "libs/bootcamp/UART_buffer.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"












void test_UART_buffer_init(void){



    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    do {if ((uBuf)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(20)));}} while(0);



    free(test_rBuffer);

    free(test_tBuffer);

    circularBuffer_free(test_cTBuffer);

    circularBuffer_free(test_cRBuffer);

    UART_buffer_free(uBuf);



}



void test_UART_buffer_receiveOne(void){



    volatile uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    volatile uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    volatile circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    volatile circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    volatile UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 128;

    UDR0 = 10;

    int8_t data;

    int8_t code = UART_buffer_receive(uBuf);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((code)), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT8);

    circularBuffer_read(test_cRBuffer,&data);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((10)), (UNITY_INT)(UNITY_UINT8 )((data)), (

   ((void *)0)

   ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_UINT8);





    free(test_rBuffer);



    circularBuffer_free(test_cTBuffer);

    circularBuffer_free(test_cRBuffer);

    UART_buffer_free(uBuf);



}

void test_UART_buffer_receiveOneFF(void){



    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 128;

    UDR0 = 10;

    int8_t data;

    int8_t code = UART_buffer_receive(uBuf);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((code)), (

   ((void *)0)

   ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT8);

    circularBuffer_read(test_cRBuffer,&data);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((10)), (UNITY_INT)(UNITY_UINT8 )((data)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_UINT8);



    free(test_rBuffer);

    free(test_tBuffer);

    circularBuffer_free(test_cTBuffer);

    circularBuffer_free(test_cRBuffer);

    UART_buffer_free(uBuf);





}







void test_UART_buffer_receiveMultiple(void){



    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 128;

    uint8_t data;

    int8_t code;

    for (size_t i = 0; i < 10; i++)

    {

        UDR0 = i;

        code = UART_buffer_receive(uBuf);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((code)), (

       ((void *)0)

       ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT8);

    }



    code = UART_buffer_receive(uBuf);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((code)), (

   ((void *)0)

   ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_INT8);



    for (size_t i = 0; i < 10; i++)

    {

        circularBuffer_read(test_cRBuffer,&data);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((data)), (

       ((void *)0)

       ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_UINT8);

    }

}





void test_UART_buffer_overwrite(void){





    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 128;

    uint8_t data;

    int8_t code;



 for (size_t i = 0; i < 10 +10; i++)

    {

        UDR0 = i;

        UART_buffer_overwriteReceive(uBuf);

    }



    for (size_t i = 10; i < 10 +10; i++)

    {

        circularBuffer_read(test_cRBuffer,&data);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((i)), (UNITY_INT)(UNITY_UINT8 )((data)), (

       ((void *)0)

       ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_UINT8);

    }

}



void test_UART_buffer_transmitOne(void){



    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 32;

    int8_t code;



    code = circularBuffer_push(test_cTBuffer,10);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((code)), (

   ((void *)0)

   ), (UNITY_UINT)(177), UNITY_DISPLAY_STYLE_INT8);

    UART_buffer_transmitFromBuffer(uBuf);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((10)), (UNITY_INT)(UNITY_UINT8 )((UDR0)), (

   ((void *)0)

   ), (UNITY_UINT)(179), UNITY_DISPLAY_STYLE_UINT8);















}



void test_UART_buffer_transmitMultiple(void){



    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 32;



    for (size_t i = 0; i < 10; i++)

    {

        circularBuffer_push(test_cTBuffer,i);



    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((UART_buffer_transmitMultipleFromBuffer(uBuf,10))), (

   ((void *)0)

   ), (UNITY_UINT)(206), UNITY_DISPLAY_STYLE_INT8);

}

void test_UART_buffer_transmitFromEmpty(void){



    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 32;

    int8_t code;





    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((UART_buffer_transmitFromBuffer(uBuf))), (

   ((void *)0)

   ), (UNITY_UINT)(230), UNITY_DISPLAY_STYLE_INT8);















}



void test_UART_buffer_transmitMultipleFromEmpty(void){



    uint8_t* test_rBuffer = malloc(sizeof(uint8_t)*10);

    uint8_t* test_tBuffer = malloc(sizeof(uint8_t)*10);



    circularBuffer_t test_cRBuffer = circularBuffer_init(test_rBuffer, 10);

    circularBuffer_t test_cTBuffer = circularBuffer_init(test_tBuffer, 10);



    UART_buffer_t uBuf = UART_buffer_init(test_cRBuffer, test_cTBuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);



    UCSR0A = 32;

    int8_t code;





    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((-1)), (UNITY_INT)(UNITY_INT8 )((UART_buffer_transmitMultipleFromBuffer(uBuf,10))), (

   ((void *)0)

   ), (UNITY_UINT)(254), UNITY_DISPLAY_STYLE_INT8);

}
