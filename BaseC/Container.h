#ifndef CONTAINER_H 
#define CONTAINER_H 
#include "Base.h"
#define CONTAINER "Container"

typedef void(*Append)(struct Container*, Base*);
typedef Base*(*Get)(struct Container*, int);
typedef void(*Resize)(struct Container*, int);
typedef void(*Map)(struct Container*, BaseF);

typedef struct Container {
    Base base;
    int size;
    int upperBound;
    Append append;
    Get get;
    Resize resize;
    Map map;
} Container;

void initializeSize(Container*, int);

void initializeUpperBound(Container*, int);

void initializeAppend(Container*, Append);

void initializeGet(Container*, Get);

void initializeResize(Container*, Resize);

void initializeMap(Container*, Map);

int getSize(Container*);

void incrementSizeAndUpperBound(Container*);

void decrementSizeAndUpperBound(Container*);

void freeContainer(Container*);

#endif