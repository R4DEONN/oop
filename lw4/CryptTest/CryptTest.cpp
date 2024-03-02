#include "pch.h"
#include "CppUnitTest.h"
#include "../crypt/crypt.cpp";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace CryptTest
{
	TEST_CLASS(CryptTest)
	{
	public:
		
		TEST_METHOD(Crypt1)
		{
			std::string str{ "A" };
			int key = 57;
			std::string cryptStr = CryptString(str, key);
			std::string actual = DecryptString(cryptStr, key);
			std::string expected = "A"s;

			Assert::AreNotEqual(cryptStr, str);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Crypt2)
		{
			std::string str{ "ABCDEFG" };
			int key = 0;
			std::string cryptStr = CryptString(str, key);
			std::string actual = DecryptString(cryptStr, key);
			std::string expected = "ABCDEFG"s;

			Assert::AreNotEqual(cryptStr, str);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Crypt3)
		{
			std::string str{ "ABCDEFG" };
			int key = 255;
			std::string cryptStr = CryptString(str, key);
			std::string actual = DecryptString(cryptStr, key);
			std::string expected = "ABCDEFG"s;

			Assert::AreNotEqual(cryptStr, str);
			Assert::AreEqual(expected, actual);
		}
	};
}
