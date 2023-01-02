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

int greaterThenTwoInt(Base* base)
{
	return ((Int*)base)->data > 2;
}

void writeLine(const char* string)
{
	printf("%s\n", string);
}

int main()
{
	// Base
	Base* base = createBase();
	char* baseDump = dumpBase(base);
	printf("%s\n", baseDump);
	free(baseDump);
	freeBase(base);
	// Int
	Base* integer = (Base*)createInt(0);
	baseDump = dumpBase(integer);
	printf("%s\n", baseDump);
	free(baseDump);
	freeBase(integer);
	// Item
	integer = (Base*)createInt(0);
	Base* item = (Base*)createItem(integer, NULL);
	baseDump = dumpBase(item);
	printf("%s\n", baseDump);
	free(baseDump);
	freeBase(item);
	freeBase(integer);
	// List
	Container* list = createContainerList();
	for (int i = 0; i < SIZE; i++) {
		Int* newValue = createInt(i);
		list->append(list, (Base*)newValue);
	}
	baseDump = dumpBase((Base*)list);
	writeLine("Print List with dump:");
	writeLine(baseDump);
	writeLine("Print List with map:");
	list->map(list, printInt);
	writeLine("");
	free(baseDump);
	// Array
	Container* container = createContainerArray();
	for (int i = 0; i < SIZE; i++) {
		Int* newValue = createInt(i);
		container->append(container, (Base*)newValue);
	}
	writeLine("Print Array with dump:");
	baseDump = dumpBase((Base*)container);
	writeLine(baseDump);
	free(baseDump);
	writeLine("Print Array with map:");
	container->map(container, printInt);
	writeLine("");
	// Containers and lists
	writeLine("Containers and lists:");
	Container* containers = createContainerArray();
	for (int i = 0; i < SIZE; i++) {
		Base* newContainer = (Base*) createContainerArray();
		containers->append(containers, newContainer);
	}
	containers->map(containers, printTypeWithFormat);
	printf("Container type is ");
	printType((Base*)containers);
	writeLine("");
	freeContainer(containers);

	Container* lists = createContainerList();
	for (int i = 0; i < SIZE; i++) {
		Base* newContainer = (Base*)createContainerList();
		lists->append(lists, newContainer);
	}
	lists->map(lists, printTypeWithFormat);
	printf("Container type is ");
	printType((Base*)lists);
	writeLine("");
	// concat List
	list->concat(list, lists);
	baseDump = dumpBase((Base*)list);
	writeLine("concatMethodList:");
	writeLine(baseDump);
	free(baseDump);
	freeContainer(list);
	freeContainer(lists);
	// where Array
	writeLine("whereMethodArray:");
	container->where(container, greaterThenTwoInt, printTypeWithFormat);
	freeContainer(container);
	return 0;
}		
