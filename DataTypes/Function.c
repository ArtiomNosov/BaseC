#include "Function.h"
Function* callocFunction();

void initializeFunctionArgumentTypes(Function* function, Container* argumentTypes);

void initializeFunctionPointer(Function* function, FunctionPointer functionPointer);

void initializeFunctionResultTypes(Function* function, Container* resultTypes);

Function* createFunction(Container* resultTypes, FunctionPointer functionPointer, Container* argumentTypes);

Function* copyFunction(Function* function);

char* toStringFunction(Function* function);

char* dumpFunction(Function* function);

void freeFunction(Function* function);

void initializeFunctionBase(Function* function);

void freeMethodFunction(Function* function);

Function* copyMethodFunction(Function* function);

char* toStringMethodFunction(Function* function);

char* dumpMethodFunction(Function* function);

FunctionError checkSizeAndTypes(Container* types, Container* container);

Container* callFunction(Function* function, Container* arguments);

Function* callocFunction()
{
	return (Function*)calloc(1, sizeof(Function));
}

void initializeFunctionArgumentTypes(Function* function, Container* argumentTypes)
{
	function->argumentTypes = argumentTypes;
}

void initializeFunctionPointer(Function* function, FunctionPointer functionPointer)
{
	function->functionPointer = functionPointer;
}

void initializeFunctionResultTypes(Function* function, Container* resultTypes)
{
	function->resultTypes = resultTypes;
}

Function* createFunction(Container* resultTypes, FunctionPointer functionPointer, Container* argumentTypes)
{
	Function* result = callocFunction();
	initializeFunctionBase(result);
	initializeFunctionArgumentTypes(result, argumentTypes);
	initializeFunctionPointer(result, functionPointer);
	initializeFunctionResultTypes(result, resultTypes);
	return result;
}

Function* copyFunction(Function* function)
{
	return (Function*)copyBase((Base*)function);
}

char* toStringFunction(Function* function)
{
	return toStringBase((Base*)function);
}

char* dumpFunction(Function* function)
{
	return dumpBase((Base*)function);
}

void freeFunction(Function* function)
{
	freeBase((Base*)function);
}

void initializeFunctionBase(Function* function)
{
	Base* base = (Base*)function;
	initializeTypeName(base, TYPE_NAME_FUNCTION);
	initializeFree(base, (Free)freeMethodFunction);
	initializeCopy(base, (Copy)copyMethodFunction);
	initializeToString(base, (_ToString)toStringMethodFunction);
	initializeDump(base, (Dump)dumpMethodFunction);
}

void freeMethodFunction(Function* function)
{
	freeContainer(function->argumentTypes);
	freeContainer(function->resultTypes);
	freeMethodBase((Base*)function);
}

Function* copyMethodFunction(Function* function)
{
	Container* newResultTypes = copyContainer(function->resultTypes);
	Container* newArgumentTypes = copyContainer(function->argumentTypes);
	return createFunction(newResultTypes, function->functionPointer, newArgumentTypes);
}

char* toStringMethodFunction(Function* function)
{
	return toStringMethodBase((Base*)function);
}

char* dumpMethodFunction(Function* function)
{
	char* typeName = toStringMethodFunction(function);
	char* argumentTypes = dumpContainer(function->argumentTypes);
	char* resultTypes = dumpContainer(function->resultTypes);
	char* result = concatenateStringsWithSeparator(typeName, (char*)ARGUMENT_FUNCTION, SEPARATOR);
	result = appendStringsWithSeparator(result, argumentTypes, SEPARATOR);
	result = appendStringsWithSeparator(result, (char*)RESULT_FUNCTION, SEPARATOR);
	result = appendStringsWithSeparator(result, resultTypes, SEPARATOR);
	free(typeName);
	free(argumentTypes);
	free(resultTypes);
	return result;
}

FunctionError checkSizeAndTypes(Container* types, Container* container)
{
	int isSameSize = types->size == container->size;
	if (!isSameSize)
	{
		return SIZE_ERROR;
	}
	size_t size = (size_t)types->size;
	for (size_t i = 0; i < size; i++)
	{
		char* typeFirst = toStringBase(get(types, i));
		char* typeSecond = toStringBase(get(container, i));
		if (strcmp(typeFirst, typeSecond) != 0)
			return TYPE_ERROR;
		free(typeFirst);
		free(typeSecond);
	}
	return OK_SIZE_AND_TYPES;
}

Container* callFunction(Function* function, Container* arguments)
{
	FunctionError functionError = checkSizeAndTypes(function->argumentTypes, arguments);
	assert(functionError == OK_SIZE_AND_TYPES && "Bad function call");
	Container* result = function->functionPointer(arguments);
	functionError = checkSizeAndTypes(function->resultTypes, result);
	assert(functionError == OK_SIZE_AND_TYPES && "Bad function call");
	return result;
}
