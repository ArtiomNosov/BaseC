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

char* createCopyOfString(const char* source)
{
    size_t upperBound = strlen(source);
    size_t size = upperBound + 1;
    char* result = (char*)calloc(size, sizeof(char));
    copyMemory(result, source, upperBound);
    return result;
}

char* concatenateStrings(char* stringOne, char* stringTwo)
{
    size_t sizeOne = strlen(stringOne);
    size_t sizeTwo = strlen(stringTwo);
    size_t sizeWithEndOfString = sizeOne + sizeTwo + 1;
    char* result = (char*)calloc(sizeWithEndOfString, sizeof(char));
    copyMemory(result, stringOne, sizeOne);
    copyMemory(result + sizeOne, stringOne, sizeTwo);
    return result;
}

char* concatenateStringsWithSeparator(char* stringOne, char* stringTwo, const char* separator)
{
    size_t sizeOne = strlen(stringOne);
    size_t sizeThree = strlen(separator);
    size_t sizeTwo = strlen(stringTwo);
    size_t sizeWithEndOfString = sizeOne + sizeTwo + sizeThree + 1;
    char* result = (char*)calloc(sizeWithEndOfString, sizeof(char));
    copyMemory(result, stringOne, sizeOne);
    copyMemory(result + sizeOne, separator, sizeThree);
    copyMemory(result + sizeOne + sizeThree, stringTwo, sizeTwo);
    return result;
}

int stringCompareToIndex(const char* stringOne, const char* stringTwo, size_t index)
{
    size_t stringOneLenght = strlen(stringOne);
    size_t stringTwoLenght = strlen(stringTwo);

    if (index >= stringOneLenght || index >= stringTwoLenght)
        return 0;

    for (size_t i = 0; i <= index; i++)
        if (stringOne[i] != stringTwo[i])
            return 0;

    return 1;
}

// Delete argument string and return concatinate of two argument strings with sep between them
char* appendStringsWithSeparator(char* stringForDelete, char* stringTwo, const char* separator)
{
    char* result = concatenateStringsWithSeparator(stringForDelete, stringTwo, separator);
    free(stringForDelete);
    return result;
}

// Delete argument string and return concatinate of two argument strings
char* appendStrings(char* stringForDelete, char* stringTwo)
{
    char* result = concatenateStrings(stringForDelete, stringTwo);
    free(stringForDelete);
    return result;
}