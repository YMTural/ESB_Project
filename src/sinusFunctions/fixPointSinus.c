#include <math.h>
#include "bootcamp/sinusFunctions/fixPointSinus.h"
#define FRACLENGTH 0x001F
    //Two Complement only for Integral part
    //To-do: -Signed FixPoint with Two's complement
    //          -Adjust Mask
    //          -Adjust Addition
    //          -and more

fix_point fixPointSinus_fixPointSinus(float deg){


}

fix_point fixPointSinus_add(fix_point first, fix_point second){

    //Only Integral bits are set
    unsigned short maskInt = 0xFFFF ^ FRACLENGTH;
    //Only Fraction bits are set
    unsigned short maskFrac = FRACLENGTH;

    fix_point fraction = 0;
    fix_point integral = 0;

    //Add the fractions
    if(!((first >> 15)^(second >> 15)) ){

        fraction = (first & maskFrac) + (second & maskFrac);
        if(fraction & ~FRACLENGTH){
            integral++;      
        }
    }
    else
    {
       if((first >> 15)){
            if((first & maskFrac) > (second & maskFrac)){
    
                fraction = (first & maskFrac) - (second & maskFrac);
           }else
           {
                fraction = (second & maskFrac) - (first & maskFrac);
           }
           

       }
    }
    
    fraction = (first & maskFrac) + (second & maskFrac);

    //Check for Overflow of Fraction part





}

fix_point fixPointSinus_multiply(fix_point first, fix_point second){


}

fix_point fixPointSinus_divide(fix_point first, fix_point second){


}