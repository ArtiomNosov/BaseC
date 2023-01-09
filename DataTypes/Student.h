#ifndef STUDENT_H 
#define STUDENT_H  

#include "Human.h"

#define TYPE_NAME_STUDENT "Student"

typedef struct Student {
    Human human;
} Student;

void freeStudent(Student* student);

Student* createStudent(char* name);

#endif