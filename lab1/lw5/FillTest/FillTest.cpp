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
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
				{ ' ', '#', '#', '#', '#', '#', '#', '#', ' ' },
				{ ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ' },
				{ ' ', '#', ' ', ' ', 'O', ' ', ' ', '#', ' ' },
				{ ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ' },
				{ ' ', '#', '#', '#', '#', '#', '#', '#', ' ' },
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
			};

			Assert::IsTrue(actual.matr == expected);
		}

		TEST_METHOD(ParseFile2)
		{
			std::stringstream input(" O ""\n");

			auto actual = ParseFile(input);

			matrix expected = {
				{ ' ', 'O', ' ' },
			};

			Assert::IsTrue(actual.matr == expected);
		}

		TEST_METHOD(FillMatrix1)
		{
			matrix matr = {
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
				{ ' ', '#', '#', '#', '#', '#', '#', '#', ' ' },
				{ ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ' },
				{ ' ', '#', ' ', ' ', 'O', ' ', ' ', '#', ' ' },
				{ ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ' },
				{ ' ', '#', '#', '#', '#', '#', '#', '#', ' ' },
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
			};

			FillMatrix(matr, {{4, 3}});

			matrix expected = {
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
				{ ' ', '#', '#', '#', '#', '#', '#', '#', ' ' },
				{ ' ', '#', '.', '.', '.', '.', '.', '#', ' ' },
				{ ' ', '#', '.', '.', 'O', '.', '.', '#', ' ' },
				{ ' ', '#', '.', '.', '.', '.', '.', '#', ' ' },
				{ ' ', '#', '#', '#', '#', '#', '#', '#', ' ' },
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
			};

			Assert::IsTrue(matr == expected);
		}

		TEST_METHOD(FillMatrix2)
		{
			matrix matr = {
				{ ' ', 'O', ' ' },
			};

			FillMatrix(matr, { { 1, 0 } });

			matrix expected = {
				{ '.', 'O', '.' },
			};

			Assert::IsTrue(matr == expected);
		}

		TEST_METHOD(FillMatrix3)
		{
			matrix matr = {
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
				{ ' ', '#', '#', '#', ' ', '#', '#', '#', ' ' },
				{ ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ' },
				{ ' ', '#', ' ', ' ', 'O', ' ', ' ', '#', ' ' },
				{ ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ' },
				{ ' ', '#', '#', '#', '#', '#', '#', '#', ' ' },
				{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
			};

			FillMatrix(matr, { { 4, 3 } });

			matrix expected = {
				{ '.', '.', '.', '.', '.', '.', '.', '.', '.' },
				{ '.', '#', '#', '#', '.', '#', '#', '#', '.' },
				{ '.', '#', '.', '.', '.', '.', '.', '#', '.' },
				{ '.', '#', '.', '.', 'O', '.', '.', '#', '.' },
				{ '.', '#', '.', '.', '.', '.', '.', '#', '.' },
				{ '.', '#', '#', '#', '#', '#', '#', '#', '.' },
				{ '.', '.', '.', '.', '.', '.', '.', '.', '.' },
			};

			Assert::IsTrue(matr == expected);
		}
	};
}
