#include "Container.h"

void initializeSize(Container* container, int size)
{
	container->size = size;
}

void initializeUpperBound(Container* container, int upperBound)
{
	container->upperBound = upperBound;
}

void initializeAppend(Container* container, Append append)
{
	container->append = append;
}

void initializeGet(Container* container, Get get)
{
	container->get = get;
}

void initializeResize(Container* container, Resize resize)
{
	container->resize = resize;
}

void initializeMap(Container* container, Map map)
{
	container->map = map;
}

void initializeWhere(Container* container, Where where)
{
	container->where = where;
}

void initializeConcat(Container* container, Concat concat)
{
	container->concat = concat;
}

void freeContainer(Container* container)
{
	freeBase((Base*)container);
}

int getSizeContainer(Container* container)
{
	return container->size;
}

void incrementSizeAndUpperBoundContainer(Container* container)
{
	container->size++;
	container->upperBound++;
}

void decrementSizeAndUpperBoundContainer(Container* container)
{
	container->size--;
	container->upperBound--;
}

int normalizeIndex(int size, int index)
{
	int result = MAX(0, index);
	int upperBound = size - 1;
	result = MIN(upperBound, index);
	return result;
}
