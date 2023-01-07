#ifndef CONTAINER_H 
#define CONTAINER_H 

#include "Base.h"

#define TYPE_NAME_CONTAINER "Container"

typedef void(*Append)(struct Container*, Base*);
typedef Base*(*Get)(struct Container*, int);
typedef void(*Resize)(struct Container*, int);
typedef void(*Map)(struct Container*, BaseF);
typedef void (*Where)(struct Container*, int (*) (Base*), BaseF); 
typedef void (*Concat)(struct Container*, struct Container*);
typedef size_t(*Size)(Base*);

typedef struct Container {
    Base base;
    int size;
    int upperBound;
    Append append;
    Get get;
    Resize resize;
    Map map;
    Where where;
    Concat concat;
} Container;

void initializeSize(Container* container, int);

void initializeUpperBound(Container* container, int);

void initializeAppend(Container* container, Append append);

void initializeGet(Container* container, Get get);

void initializeResize(Container* container, Resize resize);

void initializeMap(Container* container, Map map);

void initializeWhere(Container* container, Where where);

void initializeConcat(Container* container, Concat concat);

void freeContainer(Container* container);

int getSizeContainer(Container* container);

void incrementSizeAndUpperBoundContainer(Container* container);

void decrementSizeAndUpperBoundContainer(Container* container);

int normalizeIndex(int size, int index);

#endif
