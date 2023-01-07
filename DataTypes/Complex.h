#ifndef COMPLEX_H 
#define COMPLEX_H  

#include "stdio.h"

#include "Double.c"

#define TYPE_NAME_COMPLEX "Complex"
#define REAL_PART "Real"
#define IMAGINARY_PART "Imaginary"

typedef struct Complex {
    Base base;
    Double* real;
    Double* imaginary;
} Complex;

void freeComplex(Complex* complex);

Complex* createComplex(double real, double imaginary);

#endif