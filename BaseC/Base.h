#ifndef BASE_H 
#define BASE_H  

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BASE "Base"

struct Base;
typedef void(*Free)(struct Base*);
typedef void(*BaseF)(struct Base*);

typedef struct Base {
    char* typeName;
    Free free;
} Base;

void initializeTypeName(Base*, const char*);

void freeBase(Base* base);

void initializeBase(Base*);

void initializeFree(Base*, Free);

Base* callocBase();

Base* createBase();

#endif