#include "build/temp/_test_UART.c"
#include "libs/bootcamp/io.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/UART.h"








void test_UART_init(void){



    UART_init((16000000/16/9600 -1));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((16000000/16/9600 -1))), (UNITY_INT)(UNITY_UINT8 )((UBRR0L)), (

   ((void *)0)

   ), (UNITY_UINT)(11), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((16000000/16/9600 -1) >> 8)), (UNITY_INT)(UNITY_UINT8 )((UBRR0H)), (

   ((void *)0)

   ), (UNITY_UINT)(12), UNITY_DISPLAY_STYLE_UINT8);



}



void test_UART_transmit(void){



    UCSR0A = 32;

    for (size_t i = 0; i < 100; i++)

    {

        UART_transmit(i);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((i)), (UNITY_INT)(UNITY_INT8 )((UDR0)), (

       ((void *)0)

       ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_CHAR);

    }

}



void test_UART_flush(void){



    UART_flush();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((UDR0)), (UNITY_INT)(UNITY_UINT8 )((UDR0)), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);





}



void test_UART_receive(void){





    UCSR0A = 128;

    for (size_t i = 0; i < 100; i++)

    {



        UDR0 = i;

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((i)), (UNITY_INT)(UNITY_INT8 )((UART_receive())), (

       ((void *)0)

       ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_CHAR);



    }



}
