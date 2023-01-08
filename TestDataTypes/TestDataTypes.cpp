#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <string>

#include "StringAlgorithm.h"
#include "Base.h"
#include "Complex.h"
#include "String.h"
#include "Container.h"
#include "Array.h"
#include "Function.h"

#include "StringAlgorithm.c"
#include "Base.c"
#include "Complex.c"
#include "String.c"
#include "Container.c"
#include "Array.c"
#include "Function.c"

namespace TestDataTypes
{
	#define PATH_LOAD ""

	Container* sumDouble(Container* argument)
	{
		Container* results = createContainerArray();
		Double* doubleResult = createDouble(0.0);
		size_t size = argument->size;
		for (size_t i = 0; i < size; i++)
		{
			Double* currentDouble = (Double*)get(argument, i);
			doubleResult->data += currentDouble->data;
		}
		append(results, (Base*)doubleResult);
		return results;
	}

	TEST_CLASS(TestDouble)
	{
	public:
		std::string loadDoubleStirng(const char* path)
		{
			return "1.5";
		}
		double real = 0.0;
		std::string real_string = "";
		double tolerance = 0.000001;
		Double* var;
		TestDouble() 
		{
			real_string = loadDoubleStirng(PATH_LOAD);
			char* end_ptr = NULL;
			real = std::strtold(real_string.c_str(), &end_ptr);
			var = createDouble(real);
		}
		~TestDouble()
		{
			freeDouble(var);
		}
		TEST_METHOD(TestCreateDouble)
		{
			Assert::IsTrue(var != NULL);
			Assert::AreEqual(real, var->data, tolerance);
		}
		TEST_METHOD(TestCopyDouble)
		{
			Double* var2 = copyDouble(var);

			Assert::AreEqual(var->data, var2->data, tolerance);

			freeDouble(var2);
		}
		TEST_METHOD(TestToStringMethodDouble)
		{
			char* actual = toStringDouble(var);

			Assert::IsTrue(strcmp(actual, TYPE_NAME_DOUBLE) == 0);

			free(actual);
		}
		TEST_METHOD(TestDumpMethodDouble)
		{
			char* actual = dumpDouble(var);
			char* expect = concatenateStringsWithSeparator(TYPE_NAME_DOUBLE, (char*)real_string.c_str(), " ");

			size_t minLenght = MIN(strlen(actual), strlen(expect));
			size_t minUpperBound = minLenght - 1;
			Logger::WriteMessage(std::to_string(minLenght).c_str());

			Assert::IsTrue(stringCompareToIndex(actual, expect, minUpperBound));

			free(actual);
			free(expect);
		}
	};

	TEST_CLASS(TestComplex)
	{
	public:
		std::string loadComplexStirng(const char* path)
		{
			return "1.5 2.4";
		}
		double real = 0.0;
		double imaginary = 0.0;
		std::string complex_string = "";
		double tolerance = 0.000001;
		Complex* var;
		TestComplex()
		{
			complex_string = loadComplexStirng(PATH_LOAD);
			char* end_ptr = NULL;
			real = std::strtold(complex_string.c_str(), &end_ptr);
			end_ptr++; // avoid one space
			imaginary = std::strtold(end_ptr, &end_ptr);
			var = createComplex(real, imaginary);
		}
		~TestComplex()
		{
			freeComplex(var);
		}
		TEST_METHOD(TestCreateComplex)
		{
			Assert::IsTrue(var != NULL);

			Assert::AreEqual(real, var->real->data, tolerance);
			Assert::AreEqual(imaginary, var->imaginary->data, tolerance);
		}
		TEST_METHOD(TestCopyComplex)
		{
			Complex* var2 = copyComplex(var);

			Assert::AreEqual(var->real->data, var2->real->data, tolerance);
			Assert::AreEqual(var->imaginary->data, var2->imaginary->data, tolerance);

			freeComplex(var2);
		}
		TEST_METHOD(TestToStringMethodComplex)
		{
			char* actual = toStringComplex(var);

			Assert::IsTrue(strcmp(actual, TYPE_NAME_COMPLEX) == 0);

			free(actual);
		}
		TEST_METHOD(TestDumpMethodComplex)
		{
			char* actual = dumpComplex(var);
			std::string expect = std::string(TYPE_NAME_COMPLEX) + " ";
			expect += std::string(REAL_PART) + " ";
			expect += std::string(dumpDouble(var->real)) + " ";
			expect += std::string(IMAGINARY_PART) + " ";
			expect += std::string(dumpDouble(var->imaginary));

			Logger::WriteMessage(actual);
			Logger::WriteMessage("\n");
			Logger::WriteMessage(expect.c_str());
			Logger::WriteMessage("\n");

			size_t minLenght = MIN(strlen(actual), strlen(expect.c_str()));
			size_t minUpperBound = minLenght - 1;
			Logger::WriteMessage(std::to_string(minLenght).c_str());

			Assert::IsTrue(stringCompareToIndex(actual, expect.c_str(), minUpperBound));

			free(actual);
		}
	};

	TEST_CLASS(TestString)
	{
	public:
		char* loadCharPointerStirng(const char* path)
		{
			return createCopyOfString("1.5 2.4");
		}
		char* data;
		String* var;
		TestString()
		{
			data = loadCharPointerStirng(PATH_LOAD);
			var = createString(data);
		}
		~TestString()
		{
			freeString(var);
			free(data);
		}
		TEST_METHOD(TestCreateString)
		{
			Assert::IsTrue(var != NULL);

			Assert::IsTrue(strcmp(data, toCString(var)) == 0);
		}
		TEST_METHOD(TestCopyString)
		{
			String* var2 = copyString(var);

			Assert::IsTrue(strcmp(toCString(var), toCString(var2)) == 0);
			freeString(var2);
		}
		TEST_METHOD(TestToStringTypeString)
		{
			char* actual = toStringTypeString(var);

			Assert::IsTrue(strcmp(actual, TYPE_NAME_STRING) == 0);

			free(actual);
		}
		TEST_METHOD(TestDumpMethodString)
		{
			char* actual = dumpString(var);
			std::string expect = std::string(TYPE_NAME_STRING) + " ";
			expect += std::string(data);

			Logger::WriteMessage(actual);
			Logger::WriteMessage("\n");
			Logger::WriteMessage(expect.c_str());
			Logger::WriteMessage("\n");

			Assert::IsTrue(strcmp(actual, expect.c_str()) == 0);

			free(actual);
		}
		TEST_METHOD(TestSizeMethodString)
		{
			Assert::IsTrue(sizeString(var) == strlen(toCString(var)));
		}
		TEST_METHOD(TestAppendMethodString)
		{
			String* var2 = copyString(var);
			appendString(var2, var);
			
			std::string expect = std::string(data) + std::string(data);

			Assert::IsTrue(strcmp(expect.c_str(), toCString(var2)) == 0);

			freeString(var2);
		}
		TEST_METHOD(TestSizeMethodStringIfAppend)
		{
			String* var2 = copyString(var);
			appendString(var2, var);
			std::string expect = std::string(data) + std::string(data);

			Assert::IsTrue(expect.size() == sizeString(var2));

			freeString(var2);
		}
	};
	
	TEST_CLASS(TestFunction)
	{
	public:
		// TODO: add deserialize to Function type
		Container* arguments = NULL;
		Function* var = NULL;
		Container* results = NULL;
		double tolerance = 0.000001;
		TestFunction()
		{
			arguments = createContainerArray();
			results = createContainerArray();
			Base* doubleResult = (Base*)createDouble(0.0);
			append(results, doubleResult);
			Base* doubleArgumentFirst = (Base*)createDouble(0.0);
			Base* doubleArgumentSecond = (Base*)createDouble(0.0);
			Base* doubleArgumentThird = (Base*)createDouble(0.0);
			append(arguments, doubleArgumentFirst);
			append(arguments, doubleArgumentSecond);
			append(arguments, doubleArgumentThird);
			var = createFunction(results, sumDouble, arguments);
		}
		~TestFunction()
		{
			freeFunction(var);
		}
		TEST_METHOD(TestCreateFunction)
		{
			Assert::IsTrue(var != NULL);
			Assert::AreEqual((size_t)var->resultTypes, (size_t)results);
			Assert::AreEqual((size_t)var->argumentTypes, (size_t)arguments);
			Assert::AreEqual((size_t)var->functionPointer, (size_t)sumDouble);
		}
		TEST_METHOD(TestCopyFunction)
		{
			Function* var2 = copyFunction(var);

			Assert::IsTrue(var->resultTypes != var2->resultTypes);
			Assert::IsTrue(var->argumentTypes != var2->argumentTypes);

			freeFunction(var2);
		}
		TEST_METHOD(TestToStringMethodFunction)
		{
			char* actual = toStringFunction(var);

			Assert::IsTrue(strcmp(actual, TYPE_NAME_FUNCTION) == 0);

			free(actual);
		}
		TEST_METHOD(TestDumpMethodFunction)
		{
			char* actual = dumpFunction(var);
			std::string expect = std::string(TYPE_NAME_FUNCTION) + " ";
			expect += std::string(ARGUMENT_FUNCTION) + " ";
			expect += std::string(dumpContainer(var->argumentTypes)) + " ";
			expect += std::string(RESULT_FUNCTION) + " ";
			expect += std::string(dumpContainer(var->resultTypes));

			Logger::WriteMessage(expect.c_str());
			Logger::WriteMessage("\n");
			Logger::WriteMessage(actual);
			Assert::IsTrue(strcmp(expect.c_str(), actual) == 0);

			free(actual);
		}
		TEST_METHOD(TestCallFunction)
		{
			Container* argumentForSum = createContainerArray();
			Base* doubleArgumentFirst = (Base*)createDouble(1.0);
			Base* doubleArgumentSecond = (Base*)createDouble(2.0);
			Base* doubleArgumentThird = (Base*)createDouble(3.0);
			append(argumentForSum, doubleArgumentFirst);
			append(argumentForSum, doubleArgumentSecond);
			append(argumentForSum, doubleArgumentThird);

			Container* resultOfSum = callFunction(var, argumentForSum);
			Assert::AreEqual(((Double*)get(resultOfSum, 0))->data, 6.0, tolerance);

			char* resultDump = dumpContainer(resultOfSum);
			Logger::WriteMessage(resultDump);
			free(resultDump);

			freeContainer(argumentForSum);
			freeContainer(resultOfSum);
		}
	};
}
