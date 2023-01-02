#ifndef STRING_ALGORITHM_H 
#define STRING_ALGORITHM_H   

#include <stdlib.h>
#include <string.h>

#define LENGHT_OF_CONST_MEMORY(MEMORY) sizeof(MEMORY)/sizeof(MEMORY[0])

void copyMemory(void* destination, const void* source, size_t size);

void* createCopyOfMemory(const void* source, size_t size);

char* createCopyOfString(const char* source, size_t size);

#endif