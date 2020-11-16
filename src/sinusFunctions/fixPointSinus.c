#include <math.h>
#include "bootcamp/sinusFunctions/fixPointSinus.h"
#define FRACLENGTH 0x001F

    //To-do: -Signed FixPoint with Two's complement
    //          -Adjust Mask
    //          -Adjust Addition
    //          -and more

fix_point fixPointSinus(float deg){


}

fix_point addFixPoints(fix_point first, fix_point second){

    //Only Integral bits are set
    unsigned short maskInt = 0xFFFF ^ FRACLENGTH;
    //Only Fraction bits are set
    unsigned short maskFrac = FRACLENGTH;
    unsigned short mem = 0;

    //Add the fractions
    mem = (first & maskFrac) + (second & maskFrac);

    //Check for Overflow of Fraction part
    if(mem & ~FRACLENGTH){




    }





}

fix_point multiplyFixPoints(fix_point first, fix_point second){


}

fix_point divideFixPoints(fix_point first, fix_point second){


}