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
		
		TEST_METHOD(Crypt)
		{
			std::string str{ "A" };
			int key = 57;
			std::string cryptStr = CryptString(str, key);
			std::string actual = DecryptString(cryptStr, key);
			std::string expected = "A"s;

			Assert::AreNotEqual(cryptStr, str);
			Assert::AreEqual(expected, actual);
		}
	};
}
