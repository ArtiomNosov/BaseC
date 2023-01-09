#ifndef HUMAN_H 
#define HUMAN_H  

#include "Base.h"

#define TYPE_NAME_HUMAN "Human"
#define NAME_HUMAN "Name"

typedef struct Human {
    Base base;
    char* name;
} Human;

void freeHuman(Human* human);

Human* createHuman(char* name);

void initializeHuman(Human* human, char* name);

#endif