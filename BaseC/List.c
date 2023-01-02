#include "List.h"

void freeMethodList(List* list);

List* copyMethodList(List* list);

char* toStringMethodList(List* list);

char* dumpMethodList(List* list);

void appendMethodList(List* list, Base* data);

void pushBack(List* list, Base* data);

Base* getMethodList(List* list, int index);

void resizeMethodList(List* list, int newSize);

void mapMethodList(List* list, BaseF baseF);

void whereMethodList(List* list, int (*f) (Base*), BaseF baseF);

void concatMethodList(List* listOne, List* listTwo);

int sizeList(List* list);

List* callocList();

void initializeList(List* list);

Container* createContainerList()
{
    List* result = callocList();
    initializeList(result);
    return (Container*)result;
}

List* callocList() 
{
    return (List*)calloc(1, sizeof(List));
}

void freeList(List* list)
{
    freeBase((Base*)list);
}

List* copyMethodList(List* list)
{
    List* newList = callocList();
    initializeList(newList);
    Item* ptr = list->head;
    while (ptr) {
        Base* data = ptr->data;
        appendMethodList(newList, copyBase(data));
        ptr = ptr->next;
    }
    return newList;
}

char* toStringMethodList(List* list)
{
    return toStringMethodBase((Base*)list);
}

char* dumpMethodList(List* list)
{
    char* result = toStringMethodList(list);
    Item* ptr = list->head;
    while (ptr) {
        char* itemDump = dumpBase(ptr);
        char* oldResult = result;
        result = concatenateStringsWithSeparator(result, itemDump, SEPARATOR);
        free(oldResult);
        free(itemDump);
        ptr = ptr->next;
    }
    return result;
}

void initializeList(List* list)
{
    Container* container = (Container*)list;
    Base* base = (Base*)list;
    initializeTypeName(base, TYPE_NAME_LIST);
    initializeFree(base, (Free)freeMethodList);
    initializeCopy(base, (Copy)copyMethodList);
    initializeToString(base, (ToString)toStringMethodList);
    initializeDump(base, (Dump)dumpMethodList);
    initializeSize(container, 0);
    initializeUpperBound(container, -1);
    initializeAppend(container, (Append)appendMethodList);
    initializeGet(container, (Get)getMethodList);
    initializeResize(container, (Resize)resizeMethodList);
    initializeMap(container, (Map)mapMethodList);
    initializeWhere(container, (Where)whereMethodList);
    initializeConcat(container, (Concat)concatMethodList);
}

void appendMethodList(List* list, Base* data)
{
    pushBack(list, data);
}

void pushBack(List* list, Base* data) {
    Item* mewItem = createItem(data, NULL);

    if (!list->head) {
        list->head = mewItem;
        list->tail = mewItem;
    }
    else {
        list->tail->next = mewItem;
        list->tail = mewItem;
    }
    incrementSizeAndUpperBoundContainer((Container*)list);
}

Base* getMethodList(List* list, int index)
{
    Item* item = list->head;
    Base* res = 0;
    for (int i = 0; item != NULL && i < index; i++)
        item = item->next;
    if (item != NULL)
        res = item->data;
    else
        assert("index out of size");
    return res;
}

// TODO: add items free if newSize < oldSize
void resizeMethodList(List* list, int newSize)
{
    assert(list != NULL);
    int oldSize = sizeList(list);
    for (int i = 0; i < newSize - oldSize; i++) {
        Base* base = createBase();
        pushBack(list, base);
    }
    if (newSize > oldSize)
        initializeSize((Container*)list, newSize);
}

void mapMethodList(List* list, BaseF baseF)
{
    Item* ptr = list->head;
    while (ptr) {
        baseF(ptr->data);
        ptr = ptr->next;
    }
}

void whereMethodList(List* list, int (*f) (Base*), BaseF baseF)
{
    Item* ptr = list->head;
    while (ptr) {
        Base* currentData = ptr->data;
        if (f(currentData) == TRUE)
            baseF(currentData);
        ptr = ptr->next;
    }
}
void concatMethodList(List* listOne, List* listTwo)
{
    Item* ptr = listTwo->head;
    while (ptr) {
        Base* copyValue = copyBase(ptr->data);
        appendMethodList(listOne, copyValue);
        ptr = ptr->next;
    }
}

void freeMethodList(List* list) {
    Item* ptr = list->head, * ptr_prev;
    mapMethodList(list, freeBase);
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        freeItem(ptr_prev);
    }
    freeMethodBase((Base*)list);
}

// TODO: transform to sizeMethodList
int sizeList(List* list)
{
    assert(list != NULL);
    return ((Container*)list)->size;
}

// TODO: use somewhere
void remove(List* list, Base* data) {
    Item* ptr = list->head, * ptr_prev = NULL;
    while (ptr && ptr->data != data) {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr) {
        return;
    }
    if (ptr == list->head) {
        list->head = ptr->next;
    }
    if (ptr == list->tail) {
        list->tail = ptr_prev;
    }
    if (ptr_prev) {
        ptr_prev->next = ptr->next;
    }
    freeItem(ptr);
    decrementSizeAndUpperBoundContainer((Container*)list);
}

// TODO: use somewhere
Base* popFront(List* list)
{
    assert(list != NULL);
    assert(list->head != NULL);

    Base* res = list->head->data;
    remove(list, res);

    decrementSizeAndUpperBoundContainer((Container*)list);
    return res;
}

// TODO: use somewhere, setMethodList
int setValueInList(List* list, int index, Base* data)
{
    Item* ptr = list->head;
    for (int i = 0; ptr != NULL && i < index; i++)
        ptr = ptr->next;
    if (ptr != NULL)
        ptr->data = data;
    else
        return 1;
    return 0;
}
