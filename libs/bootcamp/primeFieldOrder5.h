#ifndef PRIMEFIELDORDER5_H
#define PRIMEFIELDORDER5_H

#include <inttypes.h>

uint8_t primeFieldOrder5_add(uint8_t a, uint8_t b);
uint8_t primeFieldOrder5_multiply(uint8_t a, uint8_t b);

/**
 * TODO: Example functionality to add:
 *  - uint8_t primeFieldOrder5_getEquivalencyClass(uint8_t a)
 *  - uint8_t primeFieldOrder5_getAdditiveInverse(uint8_t a)
 *  - uint8_t primeFieldOrder5_getMultiplicativeInverse(uint8_t a)  // consider what should happen with a = 0?
 *  - extend module in order to use other modulus p (with p always being a prime number)
 */

#endif // PRIMEFIELDORDER5_H
