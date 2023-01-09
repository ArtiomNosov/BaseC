#include "Student.h"

Student* callocStudent()
{
	return (Student*)calloc(1, sizeof(Student));
}

Student* createStudent(char* name)
{
	Student* result = callocStudent();
	initializeStudent(result, name);
	return result;
}

Student* copyStudent(Student* student)
{
	return (Student*)copyBase((Base*)student);
}

char* toStringStudent(Student* student)
{
	return toStringBase((Base*)student);
}

char* dumpStudent(Student* student)
{
	return dumpBase((Base*)student);
}

void freeStudent(Student* student)
{
	freeBase((Base*)student);
}

void initializeStudent(Student* student, char* name)
{
	initializeHuman(&student->human, name);
}
