#include "Base.h"

void initializeBase(Base* base);

Base* createBase()
{
    Base* base = callocBase();
    initializeBase(base);
    return base;
}

Base* callocBase()
{
    return calloc(1, sizeof(Base));
}

void freeBase(Base* base)
{
    base->free(base);
}

void freeMethodBase(Base* base)
{
    free(base->typeName);
    free(base);
}

void initializeBase(Base* base)
{
    initializeTypeName(base, TYPE_NAME_BASE);
    initializeFree(base, freeMethodBase);
}

void initializeTypeName(Base* base, const char* typeName)
{
    size_t typeNameLenght = strlen(typeName);
    size_t typeNameLenghtWithEnd = typeNameLenght + 1;
    base->typeName = createCopyOfString(typeName, typeNameLenghtWithEnd);
}

void initializeFree(Base* base, Free free)
{
    base->free = free;
}
