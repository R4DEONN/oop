#include "pch.h"
#include "CppUnitTest.h"
#include "../Dictionary/Dictionary.cpp"
#include "sstream"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DictionaryTest
{
	TEST_CLASS(DictionaryTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::stringstream input{
				"cat кот кошка\n"
				"ball м€ч"
			};

			auto actual = GetDictionaryFromStream(input);
			std::map<std::string, std::vector<std::string>> expected = {
				{ "cat", { "кот", "кошка" } },
				{ "ball", { "м€ч" } }
			};
		}

		TEST_METHOD(GetWordsFromString1)
		{
			std::string str = "кот, кошка, котейка";

			auto actual = GetWordsFromString(str);
			std::vector<std::string> expected = { 
				"кот",
				"кошка",
				"котейка"
			};

			Assert::IsTrue(actual == expected);
		}
	};
}
