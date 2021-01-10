#include "bootcamp/sinusFunctions/sinusFunction.h"

#define PI 3.141592


float mySinusFunction(float deg)
{

    uint8_t accuracy = 15;
    //Calculating deg % 2*PI since sin x is periodic
    float input = fmod(deg * (PI/180),2*PI);
    float result = 0;

    for(uint8_t i = 1; i < accuracy; i++){

        //Taylor Expansion for sin(x) = (-1)^n-1 * (x^2n-1)/!(2n-1)
        result += myPositivePowerFunction(-1,i-1) * (myPositivePowerFunction(input,2*i-1) / myFactorialFunction(2*i-1));

     }
    return result;


}

float myPositivePowerFunction(float x, uint8_t n)
{   
    if(n){
        float result = 1;
        for(uint8_t i = 0; i < n; i++ ){
            result = x*result;
        }
        return result;
    }
    else{
        return 1;
    }
}


float myFactorialFunction(uint8_t n)
{
    float result = 1;
    for(uint8_t i = 1; i <= n; i++){
        result = result*i;
    }
    return result;
}