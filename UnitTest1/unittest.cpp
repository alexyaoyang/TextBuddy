#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:
		
		TEST_METHOD(checksorted)
		{
			TextBuddy tb;
			tb.fileName = "mytextfile.txt";
			tb.makeFile();
			tb.writeToFile("ccc", 1);
			tb.writeToFile("bbb", 1);
			tb.writeToFile("aaa", 1);
			
			string out = "1. aaa";
			Assert::AreEqual(out, tb.getDisplayFromFile());
		}
	};
}