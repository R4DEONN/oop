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
				"cat ��� �����\n"
				"ball ���"
			};

			auto actual = GetDictionaryFromStream(input);
			std::map<std::string, std::vector<std::string>> expected = {
				{ "cat", { "���", "�����" } },
				{ "ball", { "���" } }
			};
		}

		TEST_METHOD(GetWordsFromString1)
		{
			std::string str = "���, �����, �������";

			auto actual = GetWordsFromString(str);
			std::vector<std::string> expected = { 
				"���",
				"�����",
				"�������"
			};

			Assert::IsTrue(actual == expected);
		}
	};
}
