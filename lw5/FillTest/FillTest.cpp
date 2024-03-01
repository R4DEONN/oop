#include "pch.h"
#include "CppUnitTest.h"
#include "../fill/fill.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FillTest
{
	TEST_CLASS(FillTest)
	{
	public:
		
		TEST_METHOD(ParseFile1)
		{
			std::stringstream input(
				"""\n"
				" #######""\n"
				" #     #""\n"
				" #  O  #""\n"
				" #     #""\n"
				" ####### ""\n"
				"         ""\n"
			);

			auto actual = ParseFile(input);

			matrix expected = {
				{0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 1, 1, 1, 1, 1, 1, 1, 0},
				{0, 1, 0, 0, 0, 0, 0, 1, 0},
				{0, 1, 0, 0, 2, 0, 0, 1, 0},
				{0, 1, 0, 0, 0, 0, 0, 1, 0},
				{0, 1, 1, 1, 1, 1, 1, 1, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0},
			};

			Assert::IsTrue(actual.matr == expected);
		}

		TEST_METHOD(ParseFile2)
		{
			std::stringstream input(" O ""\n");

			auto actual = ParseFile(input);

			matrix expected = {
				{ 0, 2, 0},
			};

			Assert::IsTrue(actual.matr == expected);
		}

		TEST_METHOD(FillMatrix1)
		{
			matrix matr = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 1, 1, 1, 1, 1, 1, 0 },
				{ 0, 1, 0, 0, 0, 0, 0, 1, 0 },
				{ 0, 1, 0, 0, 2, 0, 0, 1, 0 },
				{ 0, 1, 0, 0, 0, 0, 0, 1, 0 },
				{ 0, 1, 1, 1, 1, 1, 1, 1, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};

			FillMatrix(matr, {{4, 3}});

			matrix expected = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 1, 1, 1, 1, 1, 1, 0 },
				{ 0, 1, 3, 3, 3, 3, 3, 1, 0 },
				{ 0, 1, 3, 3, 2, 3, 3, 1, 0 },
				{ 0, 1, 3, 3, 3, 3, 3, 1, 0 },
				{ 0, 1, 1, 1, 1, 1, 1, 1, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};

			Assert::IsTrue(matr == expected);
		}

		TEST_METHOD(FillMatrix2)
		{
			matrix matr = {
				{ 0, 2, 0},
			};

			FillMatrix(matr, { { 1, 0 } });

			matrix expected = {
				{ 3, 2, 3 },
			};

			Assert::IsTrue(matr == expected);
		}

		TEST_METHOD(FillMatrix3)
		{
			matrix matr = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 1, 1, 0, 1, 1, 1, 0 },
				{ 0, 1, 0, 0, 0, 0, 0, 1, 0 },
				{ 0, 1, 0, 0, 2, 0, 0, 1, 0 },
				{ 0, 1, 0, 0, 0, 0, 0, 1, 0 },
				{ 0, 1, 1, 1, 1, 1, 1, 1, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};

			FillMatrix(matr, { { 4, 3 } });

			matrix expected = {
				{ 3, 3, 3, 3, 3, 3, 3, 3, 3 },
				{ 3, 1, 1, 1, 3, 1, 1, 1, 3 },
				{ 3, 1, 3, 3, 3, 3, 3, 1, 3 },
				{ 3, 1, 3, 3, 2, 3, 3, 1, 3 },
				{ 3, 1, 3, 3, 3, 3, 3, 1, 3 },
				{ 3, 1, 1, 1, 1, 1, 1, 1, 3 },
				{ 3, 3, 3, 3, 3, 3, 3, 3, 3 },
			};

			Assert::IsTrue(matr == expected);
		}
	};
}
