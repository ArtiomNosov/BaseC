#include "Professor.h"

Professor* callocProfessor()
{
	return (Professor*)calloc(1, sizeof(Professor));
}

Professor* createProfessor(char* name)
{
	Professor* result = callocProfessor();
	initializeProfessor(result, name);
	return result;
}

Professor* copyProfessor(Professor* professor)
{
	return (Professor*)copyBase((Base*)professor);
}

char* toStringProfessor(Professor* professor)
{
	return toStringBase((Base*)professor);
}

char* dumpProfessor(Professor* professor)
{
	return dumpBase((Base*)professor);
}

void freeProfessor(Professor* professor)
{
	freeBase((Base*)professor);
}

void initializeProfessor(Professor* professor, char* name)
{
	initializeHuman(&professor->human, name);
}
