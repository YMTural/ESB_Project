#include <unity.h>
#include "libs/bootcamp/primeFieldOrder5.h"

void test_addNeutralElement(void)
{
    for(uint8_t i = 0; i < 5; ++i)
    {
        TEST_ASSERT_EQUAL_UINT8(i, primeFieldOrder5_add(i, 0));
    }
}

void test_addInverseElement(void)
{
    for(uint8_t i = 0; i < 5; ++i)
    {
        uint8_t inverse = 5 - i;
        TEST_ASSERT_EQUAL_UINT8(0, primeFieldOrder5_add(i, inverse));
    }
}

void test_multiplyNeutralElement(void)
{
    for(uint8_t i = 0; i < 5; ++i)
    {
        TEST_ASSERT_EQUAL_UINT8(i, primeFieldOrder5_multiply(i, 1));
    }
}

// a * (b + c) = (a * b) + (a * c)
void test_distributiveLaw(void)
{
    for(uint8_t a = 0; a < 5; ++a)
    {
        for(uint8_t b = 0; b < 5; ++b)
        {
            for(uint8_t c = 0; c < 5; ++c)
            {
                TEST_ASSERT_EQUAL_UINT8(
                    primeFieldOrder5_multiply(a, primeFieldOrder5_add(b, c)),
                    primeFieldOrder5_add(primeFieldOrder5_multiply(a, b), primeFieldOrder5_multiply(a, c))
                );
            }
        }
    }
}

/**
 * TODO: Come up with other test cases that:
 *  - test for all the arithmetic properties required from a field
 *  - verify correct behaviour for numbers n > 4 (equivalency classes!)
 *  - explore boundary cases and possibly problematic inputs
 */
