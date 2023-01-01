#include "Int.h"

void freeInt(Int* integer)
{
	freeBase((Base*)integer);
}

void initializeDataInInteger(Int* integer, int data)
{
	integer->data = data;
}

Int* createInt(int integer)
{
	Int* result = (Int*)calloc(1, sizeof(Int));
	initializeDataInInteger(result, integer);
	Base* base = (Base*)result;
	initializeTypeName(base, INT);
	initializeFree(base, (Free)freeInt);
	return result;
}
