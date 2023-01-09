#include "Char.h"

Char* callocChar()
{
	return (Char*)calloc(1, sizeof(Char));
}

Char* createChar(UTF_16 symbol)
{
	Char* result = callocChar();
	initializeChar(result, symbol);
	return result;
}

Char* copyChar(Char* _char)
{
	return (Char*)copyBase((Base*)_char);
}

char* toStringChar(Char* _char)
{
	return toStringBase((Base*)_char);
}

char* dumpChar(Char* _char)
{
	return dumpBase((Base*)_char);
}

void freeChar(Char* _char)
{
	freeBase((Base*)_char);
}

void initializeBaseChar(Char* _char)
{
	Base* base = (Base*)_char;
	initializeTypeName(base, TYPE_NAME_CHAR);
	initializeFree(base, (Free)freeMethodChar);
	initializeCopy(base, (Copy)copyMethodChar);
	initializeToString(base, (_ToString)toStringMethodChar);
	initializeDump(base, (Dump)dumpMethodChar);
}

void initializeSymbolInChar(Char* _char, UTF_16 symbol)
{
	_char->symbol = symbol;
}

void initializeChar(Char* _char, UTF_16 symbol)
{
	initializeBaseChar(_char);
	initializeSymbolInChar(_char, symbol);
}

void freeMethodChar(Char* _char)
{
	freeMethodBase((Base*)_char);
}

Char* copyMethodChar(Char* _char)
{
	return createChar(_char->symbol);
}

String* toStringMethodChar(Char* _char)
{
	return toStringMethodBase((Base*)_char);
}

// TODO: add if else statments for getLanguage, getCaseType, getSymbolType in UTF-16 encoding
String* getLanguage(_char)
{
	return createCharStringFromCString(RUSSIAN);
}

String* getCaseType(_char)
{
	return createCharStringFromCString(UPPER_CASE);
}

String* getSymbolType(_char)
{
	return createCharStringFromCString(LETTERS_TYPE);
}

// TODO: Finish him!
String* dumpMethodChar(Char* _char)
{
	LANGUAGE_CHAR
	String* language = getLanguage(_char);
	CASE_TYPE_CHAR
	String* caseType = getCaseType(_char);
	SYMBOL_TYPE_CHAR
	String* symbolType = getSymbolType(_char);
	char* typeName = toStringMethodChar(_char);
	String* typeNameString = createCharStringFromCString(typeName);
	free(typeName);
	String* result = typeNameString;
	appendString(result, )
	return typeName;
}

void stringCopyCStringToUTFArray(UTF_16* utfString, char* cString)
{
	for (size_t i = 0; utfString[i] != '\0' && cString[i] != '\0'; i++)
		utfString[i] = cString[i];
}

Char* createCharArrayFromCString(char* cString)
{
	size_t lenghtWithUpperBound = strlen(cString) + 1;
	UTF_16* dataUTF_16 = (UTF_16*)calloc(lenghtWithUpperBound, sizeof(UTF_16));
	stringCopyCStringToUTFArray(dataUTF_16, cString);
	return dataUTF_16;
}
