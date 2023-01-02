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
	int result = max(0, index);
	int upperBound = size - 1;
	result = min(upperBound, index);
	return result;
}
