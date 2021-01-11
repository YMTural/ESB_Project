#include "build/temp/_test_mySinusFunction.c"
#include "libs/bootcamp/sinusFunctions/sinusFunction.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
















void test_zeroPower(void){



    for(int i = -25; i < 25;i++){



        UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((1)), (UNITY_FLOAT)((myPositivePowerFunction(i,0))), (

       ((void *)0)

       ), (UNITY_UINT)(16));

    }

}



void test_negativeBase(void){



    for(int i = -25; i < 0;i++){



        UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f*pow(i,i+25))), (UNITY_FLOAT)((pow(i,i+25))), (UNITY_FLOAT)((myPositivePowerFunction(i,i+25))), (

       ((void *)0)

       ), (UNITY_UINT)(24));

    }

}



void test_positiveBase(void){



    for(int i = 0; i < 25;i++){



        UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f*pow(25,i+25))), (UNITY_FLOAT)((pow(i,i+25))), (UNITY_FLOAT)((myPositivePowerFunction(i,i+25))), (

       ((void *)0)

       ), (UNITY_UINT)(32));

    }

}



void test_floatBase(void){



    for(int i = 1; i < 25; i++){



        UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((pow(1/i,25 +i))), (UNITY_FLOAT)((myPositivePowerFunction(1/i,25 +i))), (

       ((void *)0)

       ), (UNITY_UINT)(40));

    }

}



void test_exponentAddition(void){



        for(int i = 1; i < 25; i++){



        UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f*myPositivePowerFunction(i,2*i+3))), (UNITY_FLOAT)((myPositivePowerFunction(i,2*i+3))), (UNITY_FLOAT)((myPositivePowerFunction(i,i+1)*myPositivePowerFunction(i,i+2))), (

       ((void *)0)

       ), (UNITY_UINT)(48));

    }



}



void test_exponentSubtraction(void){



        for(int i = 1; i < 25; i++){



        UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f*myPositivePowerFunction(i,1))), (UNITY_FLOAT)((myPositivePowerFunction(i,1))), (UNITY_FLOAT)((myPositivePowerFunction(i,i+2)/myPositivePowerFunction(i,i+1))), (

       ((void *)0)

       ), (UNITY_UINT)(57));

    }



}



void test_ZeroFactorial(void){



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((1)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((1))), (UNITY_FLOAT)((UNITY_FLOAT)((myFactorialFunction(0)))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(64)));



}



void test_positiveFactorial(void){



    for(int i = 1; i < 20; i++){



          UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f * tgamma(i+1))), (UNITY_FLOAT)((tgamma(i+1))), (UNITY_FLOAT)((myFactorialFunction(i))), (

         ((void *)0)

         ), (UNITY_UINT)(72));

    }



}



void test_sin(void){



    for(int i = 0; i < 7200;i++){





        UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((sin(i*0.1*(3.141592/180)))), (UNITY_FLOAT)((mySinusFunction(0.1*i))), (

       ((void *)0)

       ), (UNITY_UINT)(82));



    }



}
