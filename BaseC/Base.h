#ifndef BASE_H 
#define BASE_H  

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "StringAlgorithm.h"

#define TYPE_NAME_BASE "Base"
#define TRUE 1
#define FALSE 0

struct Base;

typedef void(*Free)(struct Base*);
typedef void(*BaseF)(struct Base*);
typedef struct Base*(*Copy)(struct Base*);
typedef char*(*ToString)(struct Base*);
typedef ToString Dump;

typedef struct Base {
    char* typeName;
    Free free;
    Copy copy;
    ToString toString;
    Dump dump;
} Base;

Base* createBase();

Base* callocBase();

void freeBase(Base* base);

Base* copyBase(Base* base);

char* toStringBase(Base* base);

char* dumpBase(Base* base);

void freeMethodBase(Base* base);

char* toStringMethodBase(Base* base);

char* dumpMethodBase(Base* base);

void initializeTypeName(Base* base, const char* typeName);

void initializeFree(Base* base, Free free);

void initializeCopy(Base* base, Copy copy);

void initializeToString(Base* base, ToString toString);

void initializeDump(Base* base, Dump dump);

#endif