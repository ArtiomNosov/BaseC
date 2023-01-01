#ifndef ARRAY_H 
#define ARRAY_H  

#include "Container.h"
#define ARRAY "Array"
#define START_SIZE 2
#define SIZE_TO_REAL_SIZE 2

typedef struct Array {
    Container container;
    Base** data;
    int realSize;
} Array;

void initializeArray(Array*);

void initializeRealSizeAndData(Array*);

Array* callocArray();

Container* createContainerArray();

#endif