#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:
		TextBuddy tb;
		TEST_METHOD(checkfilename)
		{
			tb.fileName = "mytextfile.txt";
			string out = "mytextfile.txt";
			Assert::AreEqual(out, tb.fileName);
		}
		TEST_METHOD(checksorted)
		{	
			tb.makeFile();
			tb.delegateTaskWithCommand("add ccc");
			tb.closeFiles();
			string out = "1. aaa";
			Assert::AreEqual(out, tb.getDisplayFromFile());
		}
	};
}