#include "Item.h"

Item* callocItem();

Item* copyMethodItem(Item* item);

char* toStringMethodItem(Item* item);

char* dumpMethodItem(Item* item);

void initializeDataInItem(Item* item, Base* data);

void initializeNextInItem(Item* item, Item* next);

Item* createItem(Base* data, Item* next)
{
    Item* result = callocItem();
    Base* base = (Base*)result;
    initializeTypeName(base, TYPE_NAME_ITEM);
    initializeFree(base, freeMethodBase);
    initializeCopy(base, (Copy)copyMethodItem);
    initializeToString(base, (ToString)toStringMethodItem);
    initializeDump(base, (Dump)dumpMethodItem);
    initializeDataInItem(result, data);
    initializeNextInItem(result, next);
    return result;
}

void freeItem(Item* item)
{
    freeBase((Base*)item);
}

Item* callocItem()
{
    return (Item*)calloc(1, sizeof(Item));
}

Item* copyMethodItem(Item* item)
{
    return createItem(copyBase(item->data), item->next);
}

char* toStringMethodItem(Item* item)
{
    return toStringMethodBase((Base*)item);
}

char* dumpMethodItem(Item* item)
{
    char* typeName = toStringMethodItem(item);
    char* data = dumpBase(item->data);
    char* result = concatenateStringsWithSeparator(typeName, data, SEPARATOR);
    free(typeName);
    free(data);
    return result;
}

void initializeDataInItem(Item* item, Base* data)
{
    item->data = data;
}

void initializeNextInItem(Item* item, Item* next)
{
    item->next = next;
}
