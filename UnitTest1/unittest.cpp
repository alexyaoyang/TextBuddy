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
		TEST_METHOD(checkEmptySorted)
		{
			tb.getReadyToTest();
			string out = "Empty File!";
			Assert::AreEqual(out, tb.returnSorted(0));
		}
		TEST_METHOD(checkFirstSorted)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc"); 
			tb.closeFiles();
			tb.getParamAdd("add bbb");
			tb.closeFiles();
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "aaa";
			Assert::AreEqual(out, tb.returnSorted(0));
		}
		TEST_METHOD(checkLastSorted)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.closeFiles();
			tb.getParamAdd("add bbb");
			tb.closeFiles();
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "ccc";
			Assert::AreEqual(out, tb.returnSorted(1));
		}
		TEST_METHOD(checkEmptySearch)
		{
			tb.getReadyToTest();
			string out = tb.fileName + " is empty";
			Assert::AreEqual(out, tb.returnSearch("aa"));
		}
		TEST_METHOD(checkSearchNotFound)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.closeFiles();
			tb.getParamAdd("add bbb");
			tb.closeFiles();
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "No results found!";
			Assert::AreEqual(out, tb.returnSearch("cba"));
		}
		TEST_METHOD(checkSearch1)
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
		TEST_METHOD(checkSearch2)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.closeFiles();
			tb.getParamAdd("add bbb");
			tb.closeFiles();
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "1. bbb";
			Assert::AreEqual(out, tb.returnSearch("b"));
		}
		TEST_METHOD(checkSearch3)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.closeFiles();
			tb.getParamAdd("add bbb");
			tb.closeFiles();
			tb.getParamAdd("add aaa");
			tb.closeFiles();
			string out = "1. ccc";
			Assert::AreEqual(out, tb.returnSearch("c"));
		}
	};
}