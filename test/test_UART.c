#include "bootcamp/UART.h"
#include <unity.h>
#include "bootcamp/io.h"
#define RUNS 100


void test_UART_init(void){

    UART_init(MYUBRR);

    TEST_ASSERT_EQUAL_UINT8(MYUBRR,UBRR0L);
    TEST_ASSERT_EQUAL_UINT8(MYUBRR >> 8,UBRR0H);

}

void test_UART_transmit(void){
    //Set register for transmit
    UCSR0A = 32;
    for (size_t i = 0; i < RUNS; i++)
    {
        UART_transmit(i);
        TEST_ASSERT_EQUAL_CHAR(i,UDR0);
    }
}

void test_UART_flush(void){
   
    UART_flush();
    TEST_ASSERT_EQUAL_UINT8(UDR0,UDR0);


}

void test_UART_receive(void){
    
    //Set register for receive
    UCSR0A = 128;
    for (size_t i = 0; i < RUNS; i++)
    {
        
        UDR0 = i;
        TEST_ASSERT_EQUAL_CHAR(i,UART_receive());

    }
    
}