#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TextBuddy)
	{
	public:
		
		TEST_METHOD(displayEmptyFile)
		{
			string output = "mytextfile.txt is empty";
			Assert::AreEqual(getDisplayFromFile(), output);
		}
	};
}