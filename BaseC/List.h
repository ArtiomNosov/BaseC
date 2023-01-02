#ifndef LIST_H 
#define LIST_H  

#include "Container.h"
#include "Item.h"

#define TYPE_NAME_LIST "List"

typedef struct List {
    Container container;
    Item* head;
    Item* tail;
} List;

Container* createContainerList();

void freeList(List*);

#endif