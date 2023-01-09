#ifndef PROFESSOR_H 
#define PROFESSOR_H  

#include "Human.h"

#define TYPE_NAME_PROFESSOR "Professor"

typedef struct Professor {
    Human human;
} Professor;

void freeProfessor(Professor* student);

Professor* createProfessor(char* name);

#endif