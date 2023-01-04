#ifndef ARRAY_H 
#define ARRAY_H  

#include "Container.h"

#define TYPE_NAME_ARRAY "Array"
#define START_SIZE 2
// TODO: solve if we have some really big array then we will have a big problem
#define SIZE_TO_REAL_SIZE 2 

typedef struct Array {
    Container container;
    Base** data;
    int realSize;
} Array;

Container* createContainerArray();

void freeArray(Array* array);

#endif