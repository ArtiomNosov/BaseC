#include "Base.h"

void memoryCopy(void* destination, const void* source, size_t size)
{
    if (destination != NULL && source != NULL)
        memcpy(destination, source, size);
}

void initializeTypeName(Base* base, const char* typeName)
{
    size_t typeNameLenght = strlen(typeName);
    size_t typeNameLenghtWithEnd = typeNameLenght + 1;
    base->typeName = calloc(typeNameLenghtWithEnd, sizeof(char));
    memoryCopy(base->typeName, typeName, typeNameLenght);
}

void freeBase(Base* base)
{
    free(base->typeName);
    free(base);
}

void initializeFree(Base* base, Free free)
{
    base->free = free;
}

void initializeBase(Base* base)
{
    initializeTypeName(base, BASE);
    initializeFree(base, freeBase);
}

Base* callocBase()
{
    return calloc(1, sizeof(Base));
}

Base* createBase()
{
    Base* base = callocBase();
    initializeBase(base);
    return base;
}