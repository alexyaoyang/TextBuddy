#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TextBuddy/TextBuddy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TextBuddy)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}

	};
}