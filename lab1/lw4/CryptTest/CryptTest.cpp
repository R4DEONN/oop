#include "pch.h"
#include "CppUnitTest.h"
#include "../crypt/crypt.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CryptTest
{
	TEST_CLASS(CryptTest)
	{
	public:
		TEST_METHOD(CryptCharA)
		{
			int key = 57;
			auto actual = CryptChar('A', key);
			char expected = -61;

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(DecryptCharA)
		{
			int key = 57;
			auto actual = DecryptChar(-61, key);
			char expected = 'A';

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(CryptWithDecrypt)
		{
			int key = 205;
			char ch = 'A';
			auto crypted = CryptChar(ch, key);
			auto actual = DecryptChar(crypted, key);
		
			Assert::AreNotEqual(ch, crypted);
			Assert::AreEqual(ch, actual);
		}
	};
}
