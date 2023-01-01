#include "Array.h"

int normalizeIndex(Array* array, int i)
{
    int result = max(0, i);
    int size = getSize((Container*)array);
    int upperBound = size - 1;
    result = min(upperBound, i);
    return result;
}

Base* get(Array* array, int i)
{
    i = normalizeIndex(array, i);
    return array->data[i];
}

int getSizeArray(Array* array)
{
    return getSize((Container*)array);
}

void append(Array* array, Base* value)
{
    Container* container = (Container*)array;
    int size = getSizeArray(array);
    if (size == array->realSize) {
        int nextSize = size + 1;
        container->resize(container, nextSize);
    }
    array->data[size] = value;
    incrementSizeAndUpperBound(container);
}

void mapFromTo(Array* array, BaseF baseF, int from, int to)
{
    from = normalizeIndex(array, from);
    to = normalizeIndex(array, to);
    int minIndex = min(from, to);
    to = max(from, to);
    for (int i = minIndex; i <= to; i++) {
        Base* currentValue = array->data[i];
        baseF(currentValue);
    }
}

int getUpperBound(Array* array)
{
    Container* container = (Container*)array;
    return container->upperBound;
}

void map(Array* array, BaseF baseF)
{
    int upperBound = getUpperBound(array);
    mapFromTo(array, baseF, 0, upperBound);
}

void freeDataFromTo(Array* array, int from, int to)
{
    mapFromTo(array, freeBase, from, to);
}

void freeDataInArray(Array* array)
{
    int upperBound = getUpperBound(array);
    freeDataFromTo(array, 0, upperBound);
}

void resize(Array* array, int newSize)
{
    if (newSize <= 0) {
        freeDataInArray(array);
        initializeSize((Container*)array, 0);
    }
    int size = getSizeArray(array);
    int upperBound = size - 1;
    int newRealSize = newSize * SIZE_TO_REAL_SIZE;
    if (newSize < size) {
        freeDataFromTo(array, newSize, upperBound);
        initializeSize((Container*)array, newSize);
        return;
    }
    else if (newSize == size) {
        return;
    }
    Base** newData = calloc(newRealSize, sizeof(Base*));
    memcpy(newData, array->data, sizeof(Base*) * size);
    free(array->data);
    array->data = newData;
    array->realSize = newRealSize;
}

void freeArray(Array* array)
{
    freeDataInArray(array);
    free(array->data);
    freeBase((Base*)array);
}

void initializeRealSize(Array* array, int realSize)
{
    array->realSize = realSize;
    array->data = calloc(array->realSize, sizeof(Base*));
}

void initializeArray(Array* array)
{
    Container* container = (Container*)array;
    Base* base = (Base*)array;
    initializeTypeName(base, ARRAY);
    initializeSize(container, 0);
    initializeUpperBound(container, -1);
    initializeAppend(container, (Append)append);
    initializeGet(container, (Get)get);
    initializeResize(container, (Resize)resize);
    initializeMap(container, (Map)map);
    initializeFree(base, (Free)freeArray);
    initializeRealSize(array, START_SIZE);
}

Array* callocArray()
{
    return calloc(1, sizeof(Array));
}

Container* createContainerArray()
{
    Array* result = callocArray();
    initializeArray(result);
    return (Container*)result;
}
