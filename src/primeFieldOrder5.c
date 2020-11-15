#include "libs/bootcamp/primeFieldOrder5.h"

uint8_t primeFieldOrder5_add(uint8_t a, uint8_t b){
    return (a + b) % 5;
}

uint8_t primeFieldOrder5_multiply(uint8_t a, uint8_t b){
    return (a * b) % 5;
}