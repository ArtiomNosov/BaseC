#ifndef FUNCTION_H 
#define FUNCTION_H  

#include "Base.h"
#include "Container.h"

#define TYPE_NAME_FUNCTION "Function"
#define ARGUMENT_FUNCTION "Arguments"
#define RESULT_FUNCTION "Results"

typedef Container* (*FunctionPointer)(Container*);

typedef struct Function {
    Base base;
    Container* argumentTypes;
    FunctionPointer functionPointer;
    Container* resultTypes;
} Function;

typedef enum FunctionError 
{
    OK_SIZE_AND_TYPES,
    SIZE_ERROR,
    TYPE_ERROR
} FunctionError;

void freeFunction(Function* function);

Function* createFunction(Container* resultTypes, FunctionPointer functionPointer, Container* argumentTypes);

Container* callFunction(Function* function, Container* arguments);

#endif