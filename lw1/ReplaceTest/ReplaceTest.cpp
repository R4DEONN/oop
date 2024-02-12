#include "pch.h"
#include "CppUnitTest.h"
#include "iostream"
#include "../lw1/Replace.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReplaceTest
{
	TEST_CLASS(ReplaceTest)
	{
	public:
		TEST_METHOD(RecoverReplacerAfterMismatch)
		{
            std::string line = "12312312345";
            std::string searchLine = "1231234";
            std::string replaceLine = "";
            std::string expected = "1235";

            std::string result = ReplaceString(line, searchLine, replaceLine);

            Assert::AreEqual(expected, result);
		}

        TEST_METHOD(RecoverReplacerAfterMismatch2)
        {
            std::string line = "12312412345";
            std::string searchLine = "1231234";
            std::string replaceLine = "";
            std::string expected = "12312412345";

            std::string result = ReplaceString(line, searchLine, replaceLine);

            Assert::AreEqual(expected, result);
        }

        TEST_METHOD(RecoverReplacerAfterMismatch3)
        {
            std::string line = "123123412312312345";
            std::string searchLine = "12312345";
            std::string replaceLine = "";
            std::string expected = "1231234123";

            std::string result = ReplaceString(line, searchLine, replaceLine);

            Assert::AreEqual(expected, result);
        }

        TEST_METHOD(CorrectReplaceWhenReplacementLineIncludesSearchLine)
        {
            std::string line = "ma";
            std::string searchLine = "ma";
            std::string replaceLine = "mama";
            std::string expected = "mama";

            std::string result = ReplaceString(line, searchLine, replaceLine);

            Assert::AreEqual(expected, result);
        }

        TEST_METHOD(NullSearchLineMustNotChangeLine)
        {
            std::string line = "ma";
            std::string searchLine = "";
            std::string replaceLine = "mama";
            std::string expected = "ma";

            std::string result = ReplaceString(line, searchLine, replaceLine);

            Assert::AreEqual(expected, result);
        }

        TEST_METHOD(SearchStringIsNotInTheLine)
        {
            std::string line = "Hello World!";
            std::string searchLine = "lol";
            std::string replaceLine = "mama";
            std::string expected = "Hello World!";

            std::string result = ReplaceString(line, searchLine, replaceLine);

            Assert::AreEqual(expected, result);
        }
	};
}
