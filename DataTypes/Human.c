#include "Human.h"

Human* callocHuman()
{
	return (Human*)calloc(1, sizeof(Human));
}

Human* createHuman(char* name)
{
	Human* result = callocHuman();
	void initializeHuman(human, name);
	return result;
}

Human* copyHuman(Human* human)
{
	return (Human*)copyBase((Base*)human);
}

char* toStringHuman(Human* human)
{
	return toStringBase((Base*)human);
}

char* dumpHuman(Human* human)
{
	return dumpBase((Base*)human);
}

void freeHuman(Human* human)
{
	freeBase((Base*)human);
}

void initializeBaseHuman(Human* human)
{
	Base* base = (Base*)human;
	initializeTypeName(base, TYPE_NAME_HUMAN);
	initializeFree(base, (Free)freeMethodHuman);
	initializeCopy(base, (Copy)copyMethodHuman);
	initializeToString(base, (_ToString)toStringMethodHuman);
	initializeDump(base, (Dump)dumpMethodHuman);
}

void initializeNameInHuman(Human* human, char* name)
{
	human->name = createCopyOfString(name);
}

void initializeHuman(Human* human, char* name)
{
	initializeBaseHuman(human);
	initializeNameInHuman(human, name);
}

void freeMethodHuman(Human* human)
{
	free(human->name);
	freeMethodBase((Base*)human);
}

Human* copyMethodHuman(Human* human)
{
	return createHuman(human->name);
}

char* toStringMethodHuman(Human* human)
{
	return toStringMethodBase((Base*)human);
}

char* dumpMethodHuman(Human* human)
{
	char* typeName = toStringMethodHuman(human);
	char* result = concatenateStringsWithSeparator(typeName, NAME_HUMAN, SEPARATOR);
	result = appendStringsWithSeparator(result, human->name, SEPARATOR);
	free(typeName);
	return result;
}
