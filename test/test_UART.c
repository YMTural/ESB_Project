#include "bootcamp/UART.h"
#include <unity.h>

#include "mock_io.h"
//#include "build/test/mocks/mock_io.h"

void test_UART_init(void){

    UART_init(MYUBRR);

    TEST_ASSERT_EQUAL_UINT8(MYUBRR,UBRR0L);




}