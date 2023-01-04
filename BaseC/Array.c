#include "Array.h"

Array* callocArray();

void initializeArray(Array* array);

void initializeRealSize(Array* array, int realSize);

void appendMethodArray(Array* array, Base* value);

Base* getMethodArray(Array* array, int i);

void resizeMethodArray(Array* array, int newSize);

void mapMethodArray(Array* array, BaseF baseF);

void mapFromToArray(Array* array, BaseF baseF, int from, int to);

void whereMethodArray(Array* array, int (*f) (Base*), BaseF baseF);

void concatMethodArray(Array* arrayOne, Array* arrayTwo);

char* toStringMethodArray(Array* array);

char* dumpMethodArray(Array* array);

void freeMethodArray(Array* array);

Array* copyMethodArray(Array* array);

char* toStringMethodArray(Array* array);

char* dumpMethodArray(Array* array);

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
    return (Array*)calloc(1, sizeof(Array));
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
    initializeFree(base, (Free)freeMethodArray);
    initializeCopy(base, (Copy)copyMethodArray);
    initializeToString(base, (_ToString)toStringMethodArray);
    initializeDump(base, (Dump)dumpMethodArray);
    initializeSize(container, 0);
    initializeUpperBound(container, -1);
    initializeAppend(container, (Append)appendMethodArray);
    initializeGet(container, (Get)getMethodArray);
    initializeResize(container, (Resize)resizeMethodArray);
    initializeMap(container, (Map)mapMethodArray);
    initializeWhere(container, (Where)whereMethodArray);
    initializeConcat(container, (Concat)concatMethodArray);
    initializeRealSize(array, START_SIZE);
}

void initializeRealSize(Array* array, int realSize)
{
    array->realSize = realSize;
    array->data = (Base**)calloc(array->realSize, sizeof(Base*));
}

void freeMethodArray(Array* array)
{
    freeDataInArray(array);
    free(array->data);
    freeMethodBase((Base*)array);
}

Array* copyMethodArray(Array* array)
{
    Array* result = callocArray();
    initializeArray(result);
    int size = getSizeArray(array);
    for (int i = 0; i < size; i++) {
        Base* newBase = copyBase(getMethodArray(array, i));
        appendMethodArray(result, newBase);
    }
    return result;
}

char* toStringMethodArray(Array* array)
{
    return toStringMethodBase((Base*)array);
}

char* dumpMethodArray(Array* array)
{
    int size = getSizeArray(array);
    char* result = toStringMethodArray(array);
    for (int i = 0; i < size; i++) {
        Base* currentValue = array->data[i];
        char* value = dumpBase(currentValue);
        char* oldResult = result;
        result = concatenateStringsWithSeparator(result, value, SEPARATOR);
        free(oldResult);
        free(value);
    }
    return result;
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
    Base** newData = (Base**)calloc(newRealSize, sizeof(Base*));
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
    int minIndex = MIN(from, to);
    to = MAX(from, to);
    for (int i = minIndex; i <= to; i++) {
        Base* currentValue = array->data[i];
        baseF(currentValue);
    }
}

void whereMethodArray(Array* array, int (*f) (Base*), BaseF baseF)
{
    int size = getSizeArray(array);
    for (int i = 0; i < size; i++) {
        Base* currentValue = array->data[i];
        if (f(currentValue) == TRUE)
            baseF(currentValue);
    }
}

void concatMethodArray(Array* arrayOne, Array* arrayTwo)
{
    int sizeTwo = getSizeArray(arrayTwo);
    for (int i = 0; i < sizeTwo; i++) {
        Base* copyValue = copyBase(arrayTwo->data[i]);
        appendMethodArray(arrayOne, copyValue);
    }
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
