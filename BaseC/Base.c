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

Base* copyBase(Base* base)
{
    return base->copy(base);
}

char* toStringBase(Base* base)
{
    return base->toString(base);
}

char* dumpBase(Base* base)
{
    return base->dump(base);
}

void freeMethodBase(Base* base)
{
    free(base->typeName);
    free(base);
}

Base* copyMethodBase(Base* base)
{
    return createBase();
}

char* toStringMethodBase(Base* base)
{
    char* typeName = base->typeName;
    size_t typeNameLenght = strlen(typeName);
    size_t typeNameLenghtWithEnd = typeNameLenght + 1;
    return createCopyOfString(typeName, typeNameLenghtWithEnd);
}

char* dumpMethodBase(Base* base)
{
    return toStringMethodBase(base);
}

void initializeBase(Base* base)
{
    initializeTypeName(base, TYPE_NAME_BASE);
    initializeFree(base, freeMethodBase);
    initializeCopy(base, copyMethodBase);
    initializeToString(base, toStringMethodBase);
    initializeDump(base, dumpMethodBase);
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

void initializeCopy(Base* base, Copy copy)
{
    base->copy = copy;
}

void initializeToString(Base* base, ToString toString)
{
    base->toString = toString;
}

void initializeDump(Base* base, Dump dump)
{
    base->dump = dump;
}