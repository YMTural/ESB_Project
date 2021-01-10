#define UNITY_INCLUDE_FLOAT
#include <unity.h>
#include <math.h>
#include <stdlib.h>
#include "bootcamp/sinusFunctions/sinusFunction.h"
#include <stdio.h>
#define DELTA 0.01f
#define RANGE 25
#define CONVERTDEG (3.141592/180)

//x^0
void test_zeroPower(void){

    for(int i = -RANGE; i < RANGE;i++){
        
        TEST_ASSERT_FLOAT_WITHIN(DELTA,1,myPositivePowerFunction(i,0));
    }
}
//(-x)^n
void test_negativeBase(void){
   
    for(int i = -RANGE; i < 0;i++){
        
        TEST_ASSERT_FLOAT_WITHIN(DELTA*pow(i,i+RANGE),pow(i,i+RANGE),myPositivePowerFunction(i,i+RANGE));
    }
}
//x^n
void test_positiveBase(void){

    for(int i = 0; i < RANGE;i++){
        
        TEST_ASSERT_FLOAT_WITHIN(DELTA*pow(RANGE,i+RANGE),pow(i,i+RANGE),myPositivePowerFunction(i,i+RANGE));
    }
}
//(x/y)^n      
void test_floatBase(void){

    for(int i = 1; i < RANGE; i++){

        TEST_ASSERT_FLOAT_WITHIN(DELTA,pow(1/i,RANGE+i),myPositivePowerFunction(1/i,RANGE+i));
    }
}
//x^n * x^m = x^n+m
void test_exponentAddition(void){

        for(int i = 1; i < RANGE; i++){

        TEST_ASSERT_FLOAT_WITHIN(DELTA*myPositivePowerFunction(i,2*i+3),myPositivePowerFunction(i,2*i+3),myPositivePowerFunction(i,i+1)*myPositivePowerFunction(i,i+2));
    }

}
//x^n / x^m = x^n-m
void test_exponentSubtraction(void){

        for(int i = 1; i < RANGE; i++){

        TEST_ASSERT_FLOAT_WITHIN(DELTA*myPositivePowerFunction(i,1),myPositivePowerFunction(i,1),myPositivePowerFunction(i,i+2)/myPositivePowerFunction(i,i+1));
    }

}
//!0 = 1
void test_ZeroFactorial(void){

    TEST_ASSERT_EQUAL_FLOAT(1,myFactorialFunction(0));

}
//!n
void test_positiveFactorial(void){

    for(int i = 1; i < 20; i++){

          TEST_ASSERT_FLOAT_WITHIN(DELTA * tgamma(i+1) ,tgamma(i+1),myFactorialFunction(i));
    }

}
//Every 10th of a Degree
void test_sin(void){

    for(int i = 0; i < 7200;i++){
        //sin form math.h expects value as RAD
        
        TEST_ASSERT_FLOAT_WITHIN(DELTA, sin(i*0.1*CONVERTDEG), mySinusFunction(0.1*i));

    }

}