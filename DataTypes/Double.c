#include "Double.h"

void initializeDouble(Double* real);

void initializeDataInDouble(Double* real, double data);

Double* copyMethodDouble(Double* real);

char* toStringMethodDouble(Double* real);

char* dumpMethodDouble(Double* real);

Double* createDouble(double data)
{
	Double* result = (Double*)calloc(1, sizeof(Double));
	initializeDouble(result);
	initializeDataInDouble(result, data);
	return result;
}

void freeDouble(Double* real)
{
	freeBase((Base*)real);
}

void initializeDouble(Double* real)
{
	Base* base = (Base*)real;
	initializeTypeName(base, TYPE_NAME_DOUBLE);
	initializeFree(base, (Free)freeMethodBase);
	initializeCopy(base, (Copy)copyMethodDouble);
	initializeToString(base, (_ToString)toStringMethodDouble);
	initializeDump(base, (Dump)dumpMethodDouble);
}

void initializeDataInDouble(Double* real, double data)
{
	real->data = data;
}

Double* copyMethodDouble(Double* real)
{
	return createDouble(real->data);
}

char* toStringMethodDouble(Double* real)
{
	return toStringMethodBase((Base*)real);
}

char* dumpMethodDouble(Double* real)
{
	char buffer[BUFFER_SIZE] = { 0 };
	char* typeName = toStringMethodInt(real);
	sprintf(buffer, "%f", real->data);
	char* data = createCopyOfString(buffer);
	char* result = concatenateStringsWithSeparator(typeName, data, SEPARATOR);
	free(typeName);
	free(data);
	return result;
}
