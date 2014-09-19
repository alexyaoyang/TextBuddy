#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:
		TextBuddy tb;
		TEST_METHOD(checkAdded)
		{	
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			Assert::AreEqual(1, tb.getSize());
		}
		TEST_METHOD(checkSorted)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "aaa";
			Assert::AreEqual(out, tb.returnSorted());
		}
		TEST_METHOD(checkSearch)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "aaa";
			Assert::AreEqual(out, tb.returnSearch("aa"));
		}
	};
}