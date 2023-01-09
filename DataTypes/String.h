#ifndef STRING_H 
#define STRING_H  

#include "Base.h"
#include "Char.h"
#include "Container.h"
#include "StringAlgorithm.h"

#define TYPE_NAME_STRING "String"
#define UPDATE_STRING 1
#define ALREADY_GET_SIZE_STRING 2

// TODO: insert, substr, find

typedef struct String {
    Base base;
    Char* data;
    int update;
    Size size;
    Append append;
} String;

void freeString(String* str);

String* createStringFromCString(char* data);

void appendString(String* destination, String* source);

#endif