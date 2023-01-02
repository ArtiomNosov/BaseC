#ifndef ITEM_H 
#define ITEM_H  

#include "Base.h"

#define TYPE_NAME_ITEM "Item"

typedef struct Item {
    Base base;
    Base* data;
    struct Item* next;
} Item;

Item* createItem(Base* data, Item* next);

void freeItem(Item* item);

#endif