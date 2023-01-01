#ifndef LIST_H 
#define LIST_H  

#include "Container.h"
#define LIST "List"

typedef struct Item {
    Base* data;
    struct Item* next;
} Item;

typedef struct List {
    Container container;
    Item* head;
    Item* tail;
} List;

Container* createContainerList();

void freeList(List*);

#endif