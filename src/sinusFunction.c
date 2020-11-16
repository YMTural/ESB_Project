#include "bootcamp/sinusFunction.h"
#include <math.h>
#define PI 3.141592


double mySinusFunction(double deg)
{
    uint8_t accuracy = 100;
    //Calculating deg % 2*PI since sin x is periodic
    double input = remainder(deg * (PI/180),2*PI);
    double result = 0;

    for(uint8_t i = 1; i < accuracy; i++){

        //Taylor Expansion for sin(x) = (-1)^n-1 * (x^2n-1)/!(2n-1)
        result += myPositivePowerFunction(-1,i-1) * (myPositivePowerFunction(input,2*i-1) / myFactorialFunction(2*i-1));

     }
    return result;

}

double myPositivePowerFunction(double x, uint8_t n)
{   
    if(n){
        double result = 1;
        for(uint8_t i = 0; i < n; i++ ){
            result = x*result;
        }
        return result;
    }
    else{
        return 1;
    }
}


double myFactorialFunction(uint8_t n)
{
    double result = 1;
    for(uint8_t i = 1; i <= n; i++){
        result = result*i;
    }
    return result;
}