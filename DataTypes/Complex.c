#include "Complex.h"

void initializeComplex(Complex* complex);

void initializeDataInComplex(Complex* complex, double real, double imaginary);

void freeMethodComplex(Complex* complex);

Complex* copyMethodComplex(Complex* complex);

char* toStringMethodComplex(Complex* complex);

char* dumpMethodComplex(Complex* complex);

Complex* createComplex(double real, double imaginary)
{
	Complex* result = (Complex*)calloc(1, sizeof(Complex));
	initializeComplex(result);
	initializeDataInComplex(result, real, imaginary);
	return result;
}

Complex* copyComplex(Complex* complex)
{
	return (Complex*)copyBase((Base*)complex);
}

char* toStringComplex(Complex* complex)
{
	return toStringBase((Base*)complex);
}

char* dumpComplex(Complex* complex)
{
	return dumpBase((Base*)complex);
}

void freeComplex(Complex* complex)
{
	freeBase((Base*)complex);
}

void initializeComplex(Complex* complex)
{
	Base* base = (Base*)complex;
	initializeTypeName(base, TYPE_NAME_COMPLEX);
	initializeFree(base, (Free)freeMethodComplex);
	initializeCopy(base, (Copy)copyMethodComplex);
	initializeToString(base, (_ToString)toStringMethodComplex);
	initializeDump(base, (Dump)dumpMethodComplex);
}

void initializeDataInComplex(Complex* complex, double real, double imaginary)
{
	complex->real = createDouble(real);
	complex->imaginary = createDouble(imaginary);
}

void freeMethodComplex(Complex* complex)
{
	 freeBase((Base*)(complex->real));
	 freeBase((Base*)(complex->imaginary));
	 freeMethodBase((Base*)complex);
}

Complex* copyMethodComplex(Complex* complex)
{
	return createComplex(complex->real->data, complex->imaginary->data);
}

char* toStringMethodComplex(Complex* complex)
{
	return toStringMethodBase((Base*)complex);
}

char* dumpMethodComplex(Complex* complex)
{
	char* buf = NULL;
	char* typeName = toStringMethodComplex(complex);
	char* bufReal = dumpMethodDouble(complex->real);
	char* bufImaginary = dumpMethodDouble(complex->imaginary);
	char* real = concatenateStringsWithSeparator(REAL_PART, bufReal, SEPARATOR);
	char* imaginary = concatenateStringsWithSeparator(IMAGINARY_PART, bufImaginary, SEPARATOR);
	buf = concatenateStringsWithSeparator(typeName, real, SEPARATOR);
	char* result = concatenateStringsWithSeparator(buf, imaginary, SEPARATOR);
	
	free(typeName);
	free(buf);
	free(real);
	free(imaginary);
	free(bufReal);
	free(bufImaginary);
	return result;
}
