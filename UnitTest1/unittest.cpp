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
			tb.closeFiles();
			Assert::AreEqual(1, tb.getSize());
		}
		TEST_METHOD(checkSorted)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc"); 
			tb.closeFiles();
			tb.getParamAdd("add bbb");
			tb.closeFiles();
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "aaa";
			Assert::AreEqual(out, tb.returnFirstSorted());
		}
		TEST_METHOD(checkSearch)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.closeFiles();
			tb.getParamAdd("add bbb");
			tb.closeFiles();
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "1. aaa";
			Assert::AreEqual(out, tb.returnSearch("aa"));
		}
	};
}