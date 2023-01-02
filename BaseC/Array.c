#include "Array.h"

Array* callocArray();

void initializeArray(Array* array);

void initializeRealSize(Array* array, int realSize);

void appendMethodArray(Array* array, Base* value);

Base* getMethodArray(Array* array, int i);

void resizeMethodArray(Array* array, int newSize);

void mapMethodArray(Array* array, BaseF baseF);

void mapFromToArray(Array* array, BaseF baseF, int from, int to);

void freeMethodArray(Array* array);

void freeDataInArray(Array* array);

void freeDataOfArrayFromTo(Array* array, int from, int to);

int getSizeArray(Array* array);

int getUpperBoundArray(Array* array);

Container* createContainerArray()
{
    Array* result = callocArray();
    initializeArray(result);
    return (Container*)result;
}

Array* callocArray()
{
    return calloc(1, sizeof(Array));
}

void freeArray(Array* array)
{
    freeBase((Base*)array);
}

void initializeArray(Array* array)
{
    Container* container = (Container*)array;
    Base* base = (Base*)array;
    initializeTypeName(base, TYPE_NAME_ARRAY);
    initializeSize(container, 0);
    initializeUpperBound(container, -1);
    initializeAppend(container, (Append)appendMethodArray);
    initializeGet(container, (Get)getMethodArray);
    initializeResize(container, (Resize)resizeMethodArray);
    initializeMap(container, (Map)mapMethodArray);
    initializeFree(base, (Free)freeMethodArray);
    initializeRealSize(array, START_SIZE);
}

void initializeRealSize(Array* array, int realSize)
{
    array->realSize = realSize;
    array->data = calloc(array->realSize, sizeof(Base*));
}

void appendMethodArray(Array* array, Base* value)
{
    Container* container = (Container*)array;
    int size = getSizeArray(array);
    if (size == array->realSize) {
        int nextSize = size + 1;
        container->resize(container, nextSize);
    }
    array->data[size] = value;
    incrementSizeAndUpperBoundContainer(container);
}

Base* getMethodArray(Array* array, int i)
{
    int size = getSizeArray(array);
    i = normalizeIndex(size, i);
    return array->data[i];
}

void resizeMethodArray(Array* array, int newSize)
{
    if (newSize <= 0) {
        freeDataInArray(array);
        initializeSize((Container*)array, 0);
    }
    int size = getSizeArray(array);
    int upperBound = size - 1;
    int newRealSize = newSize * SIZE_TO_REAL_SIZE;
    if (newSize < size) {
        freeDataOfArrayFromTo(array, newSize, upperBound);
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

void mapMethodArray(Array* array, BaseF baseF)
{
    int upperBound = getUpperBoundArray(array);
    mapFromToArray(array, baseF, 0, upperBound);
}

void mapFromToArray(Array* array, BaseF baseF, int from, int to)
{
    int size = getSizeArray(array);
    from = normalizeIndex(size, from);
    to = normalizeIndex(size, to);
    int minIndex = min(from, to);
    to = max(from, to);
    for (int i = minIndex; i <= to; i++) {
        Base* currentValue = array->data[i];
        baseF(currentValue);
    }
}

void freeMethodArray(Array* array)
{
    freeDataInArray(array);
    free(array->data);
    freeMethodBase((Base*)array);
}

void freeDataInArray(Array* array)
{
    int upperBound = getUpperBoundArray(array);
    freeDataOfArrayFromTo(array, 0, upperBound);
}

void freeDataOfArrayFromTo(Array* array, int from, int to)
{
    mapFromToArray(array, freeMethodBase, from, to);
}

int getSizeArray(Array* array)
{
    return getSizeContainer((Container*)array);
}

int getUpperBoundArray(Array* array)
{
    return ((Container*)array)->upperBound;
}
