#include "Int.h"

void initializeInt(Int* integer);

void initializeDataInInteger(Int* integer, int data);

Int* copyMethodInt(Int* integer);

char* toStringMethodInt(Int* integer);

char* dumpMethodInt(Int* integer);

Int* createInt(int data)
{
	Int* result = (Int*)calloc(1, sizeof(Int));
	initializeInt(result);
	initializeDataInInteger(result, data);
	return result;
}

void freeInt(Int* integer)
{
	freeBase((Base*)integer);
}

void initializeInt(Int* integer)
{
	Base* base = (Base*)integer;
	initializeTypeName(base, TYPE_NAME_INT);
	initializeFree(base, (Free)freeMethodBase);
	initializeCopy(base, (Copy)copyMethodInt);
	initializeToString(base, (ToString)toStringMethodInt);
	initializeDump(base, (Dump)dumpMethodInt);
}

void initializeDataInInteger(Int* integer, int data)
{
	integer->data = data;
}

Int* copyMethodInt(Int* integer)
{
	return createInt(integer->data);
}

char* toStringMethodInt(Int* integer)
{
	return toStringMethodBase((Base*)integer);
}

char* dumpMethodInt(Int* integer)
{
	char buffer[BUFFER_SIZE] = { 0 };
	char* typeName = toStringMethodInt(integer);
	_itoa_s(integer->data, buffer, BUFFER_SIZE, DECIMAL_RADIX);
	char* data = createCopyOfString(buffer);
	char* result = concatenateStringsWithSeparator(typeName, data, SEPARATOR);
	free(typeName);
	free(data);
	return result;
}
