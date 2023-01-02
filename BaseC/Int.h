#ifndef INT_H 
#define INT_H  

#include "Base.h"

#define TYPE_NAME_INT "Integer"
#define DECIMAL_RADIX 10

typedef struct Int {
    Base base;
    int data;
} Int;

void freeInt(Int* integer);

Int* createInt(int integer);

#endif