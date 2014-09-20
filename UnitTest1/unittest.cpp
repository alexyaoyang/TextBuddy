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
		TEST_METHOD(checkEmptySorted)
		{
			tb.getReadyToTest();
			string expected = "Empty File!";
			Assert::AreEqual(expected, tb.returnSorted(0));
		}
		TEST_METHOD(checkFirstSorted)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc"); 
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			string expected = "aaa";
			Assert::AreEqual(expected, tb.returnSorted(0));
		}
		TEST_METHOD(checkLastSorted)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			string expected = "ccc";
			Assert::AreEqual(expected, tb.returnSorted(1));
		}
		TEST_METHOD(checkEmptySearch)
		{
			tb.getReadyToTest();
			string expected = tb.fileName + " is empty";
			Assert::AreEqual(expected, tb.returnSearch("aa"));
		}
		TEST_METHOD(checkSearchNotFound)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			string expected = "No results found!";
			Assert::AreEqual(expected, tb.returnSearch("abc"));
		}
		TEST_METHOD(checkSearch1)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			string expected = "1. aaa";
			Assert::AreEqual(expected, tb.returnSearch("aa"));
		}
		TEST_METHOD(checkSearch2)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			string expected = "1. bbb";
			Assert::AreEqual(expected, tb.returnSearch("b"));
		}
		TEST_METHOD(checkSearch3)
		{
			tb.getReadyToTest();
			tb.getParamAdd("add ccc");
			tb.getParamAdd("add bbb");
			tb.getParamAdd("add aaa");
			string expected = "1. ccc";
			Assert::AreEqual(expected, tb.returnSearch("c"));
		}
	};
}