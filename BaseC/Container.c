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

int getSize(Container* container)
{
	return container->size;
}

void initializeResize(Container* container, Resize resize)
{
	container->resize = resize;
}

void initializeMap(Container* container, Map map)
{
	container->map = map;
}

void incrementSizeAndUpperBound(Container* container)
{
	container->size++;
	container->upperBound++;
}

void decrementSizeAndUpperBound(Container* container)
{
	container->size--;
	container->upperBound--;
}

void freeContainer(Container* container)
{
	Base* base = (Base*)container;
	base->free(base);
}
