#include "build/temp/_test_UART.c"
#include "build/test/mocks/mock_io.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/UART.h"






void test_UART_init(void){



    UART_init((16000000/16/9600 -1));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((16000000/16/9600 -1))), (UNITY_INT)(UNITY_UINT8 )((UBRR0L)), (

   ((void *)0)

   ), (UNITY_UINT)(11), UNITY_DISPLAY_STYLE_UINT8);









}
