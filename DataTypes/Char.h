#ifndef CHAR_H 
#define CHAR_H  

#include "Base.h"
#include "String.h"
#include <stdint.h>

#define TYPE_NAME_CHAR "Char"
typedef uint16_t UTF_16;

typedef struct Char {
    Base base;
    UTF_16 symbol;
} Char;

#define LANGUAGE_CHAR "Language:"
#define RUSSIAN "Russian"

#define CASE_TYPE_CHAR "Case type:"
#define UPPER_CASE "Upper case"
#define LOWER_CASE "Lower case"

#define SYMBOL_TYPE_CHAR "Symbol type:"
#define DIGIT_TYPE "Digit"
#define LETTERS_TYPE "Letters"

void freeChar(Char* _char);

Char* createChar(UTF_16 symbol);

Char* createCharStringFromCString(char* cString);

#endif