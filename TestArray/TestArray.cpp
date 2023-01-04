#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Base.c"
#include "StringAlgorithm.c"
#include "Container.c"
#include "Array.c"

namespace TestArray
{
	TEST_CLASS(TestArray)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Container* array = createContainerArray();
			char* typeName = toStringBase((Base*)array);
			Logger::WriteMessage(typeName);
			Assert::IsTrue(strcmp(typeName, TYPE_NAME_ARRAY)==0);

			//freeBase((Base*)array);
			//free(typeName);
		}
	};
}
