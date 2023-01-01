#include <stdio.h>
#include "Array.h"
#include "List.h"
#include "Int.h"

#define SIZE 5

void printTypeWithFormat(Base* base)
{
	printf("typeName: %s\n", base->typeName);
}

void printType(Base* base)
{
	printf("%s", base->typeName);
}

void printInt(Base* base)
{
	printf("%d ", ((Int*)base)->data);
}

void writeLine()
{
	printf("\n");
}

int main()
{
	Container* container = createContainerArray();
	for (int i = 0; i < SIZE; i++) {
		Int* newValue = createInt(i);
		container->append(container, (Base*)newValue);
	}
	container->map(container, printTypeWithFormat);
	container->map(container, printInt);
	writeLine();
	freeContainer(container);

	Container* containers = createContainerArray();
	for (int i = 0; i < SIZE; i++) {
		Base* newContainer = (Base*) createContainerArray();
		containers->append(containers, newContainer);
	}
	containers->map(containers, printTypeWithFormat);
	printf("Container type is ");
	printType((Base*)containers);
	writeLine();
	freeContainer(containers);

	Container* lists = createContainerList();
	for (int i = 0; i < SIZE; i++) {
		Base* newContainer = (Base*)createContainerList();
		lists->append(lists, newContainer);
	}
	lists->map(lists, printTypeWithFormat);
	printf("Container type is ");
	printType((Base*)lists);
	writeLine();
	freeContainer(lists);

	Container* list = createContainerList();
	for (int i = 0; i < SIZE; i++) {
		Int* newValue = createInt(i);
		list->append(list, (Base*)newValue);
	}
	list->map(list, printTypeWithFormat);
	list->map(list, printInt);
	writeLine();
	freeContainer(list);
	return 0;
}		
