#ifndef FIXPOINTSINUS
#define FIXPOINTSINUS

//11bit Integral, 5bit fractional
typedef unsigned short fix_point;

fix_point fixPointSinus(float);

fix_point addFixPoints(fix_point, fix_point);

fix_point multiplyFixPoints(fix_point, fix_point);

fix_point divideFixPoints(fix_point, fix_point);

#endif