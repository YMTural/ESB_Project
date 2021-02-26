#include <unity.h>
#include "bootcamp/adc_temperature.h"
#include "bootcamp/io.h"
#include "bootcamp/interrupt.h"

void test_getTemp(void){

    ADCW = 0;
    TEST_ASSERT_EQUAL_UINT32(253, adc_temperature_getTemperature());
}