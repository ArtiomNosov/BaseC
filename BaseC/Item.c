#include "Item.h"

Item* callocItem()
{
    return (Item*)calloc(1, sizeof(Item));
}

Item* createItem()
{
    Item* result = callocItem();
    Base* base = (Base*)result;
    initializeTypeName(base, TYPE_NAME_ITEM);
    initializeFree(base, freeMethodBase);
    return result;
}

void freeItem(Item* item)
{
    freeBase((Base*)item);
}
