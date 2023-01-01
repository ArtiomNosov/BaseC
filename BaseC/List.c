#include "List.h"

Item* callocItem()
{
    return (Item*)calloc(1, sizeof(Item));
}

List* callocList() {
    return (List*)calloc(1, sizeof(List));
}

void mapList(List* list, BaseF baseF)
{
    Item* ptr = list->head;
    while (ptr) {
        baseF(ptr->data);
        ptr = ptr->next;
    }
}
void freeList(List* list) {
    Item* ptr = list->head, * ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        Base* data = ptr_prev->data;
        data->free(data);
        free(ptr_prev);
    }
    freeBase((Base*)list);
}

void pushBack(List* list, Base* data) {
    Item* ptr = callocItem();

    ptr->data = data;
    ptr->next = NULL;
    if (!list->head) {
        list->head = ptr;
        list->tail = ptr;
    }
    else {
        list->tail->next = ptr;
        list->tail = ptr;
    }
    incrementSizeAndUpperBound((Container*)list);
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
    free(ptr);
    decrementSizeAndUpperBound((Container*)list);
}

// TODO: use somewhere
Base* popFront(List* list)
{
    assert(list != NULL);
    assert(list->head != NULL);

    Base* res = list->head->data;
    remove(list, res);

    decrementSizeAndUpperBound((Container*)list);
    return res;
}

// TODO: use somewhere
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

Base* getValueFromList(List* list, int index)
{
    Item* ptr = list->head;
    Base* res = 0;
    for (int i = 0; ptr != NULL && i < index; i++)
        ptr = ptr->next;
    if (ptr != NULL)
        res = ptr->data;
    else
        assert("index out of size");
    return res;
}


int sizeList(List* list)
{
    assert(list != NULL);
    return ((Container*)list)->size;
}

void resizeList(List* list, int newSize)
{
    assert(list != NULL);
    int oldSize = sizeList(list);
    for (int i = 0; i < newSize - oldSize; i++) {
        Base* base = createBase();
        pushBack(list, base);
    }
    initializeSize((Container*)list, newSize);
}

void initializeList(List* list)
{
    Container* container = (Container*)list;
    Base* base = (Base*)list;
    initializeTypeName(base, LIST);
    initializeSize(container, 0);
    initializeUpperBound(container, -1);
    initializeAppend(container, (Append)pushBack);
    initializeGet(container, (Get)getValueFromList);
    initializeResize(container, (Resize)resizeList);
    initializeMap(container, (Map)mapList);
    initializeFree(base, (Free)freeList);
}

Container* createContainerList()
{
    List* result = callocList();
    initializeList(result);
    return (Container*)result;
}
