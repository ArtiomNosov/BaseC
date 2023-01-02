#ifndef BASE_H 
#define BASE_H  

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "StringAlgorithm.h"

#define TYPE_NAME_BASE "Base"

struct Base;

typedef void(*Free)(struct Base*);
typedef void(*BaseF)(struct Base*);

typedef struct Base {
    char* typeName;
    Free free;
} Base;

Base* createBase();

Base* callocBase();

void freeBase(Base* base);

void freeMethodBase(Base* base);

void initializeTypeName(Base* base, const char* typeName);

void initializeFree(Base* base, Free free);

#endif