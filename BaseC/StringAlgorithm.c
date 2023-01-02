#include "StringAlgorithm.h"

void copyMemory(void* destination, const void* source, size_t size)
{
    if (destination != NULL && source != NULL)
        memcpy(destination, source, size);
}

void* createCopyOfMemory(const void* source, size_t size)
{
    void* result = calloc(size, sizeof(char));
    copyMemory(result, source, size);
    return result;
}

char* createCopyOfString(const char* source, size_t size)
{
    char* result = calloc(size, sizeof(char));
    size_t upperBound = size - 1;
    copyMemory(result, source, upperBound);
    return result;
}
