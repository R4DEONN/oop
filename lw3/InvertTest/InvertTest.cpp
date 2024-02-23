#include "pch.h"
#include "CppUnitTest.h"
#include "../lw3/invert.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InvertTest
{
	TEST_CLASS(InvertTest)
	{
	public:
		TEST_METHOD(GetMatrixFromCorrectStream)
		{
			std::istringstream input("3	4	8\n2.4	-1	11\n7	-3.2	0\n");
			
			auto actual = GetMatrixFromStream(input);

			matrix expected = {{
				{3, 4, 8},
				{2.4, -1, 11},
				{7, -3.2, 0},
			}};

			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(GetMatrixFromIncorrectStreamWithException)
		{
			Assert::ExpectException<std::logic_error>([]() {
				std::istringstream input("3	4	8\n2.4	-1	11\n");
				GetMatrixFromStream(input);
			});
		}

		TEST_METHOD(GetMatrixDeterminant3x3)
		{
			matrix matr = {{
				{1, -2, 3},
				{4, 0, 6},
				{-7, 8, 9},
			}};
			auto actual = GetMatrixDeterminant(matr);

			double expected = 204;

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetMatrixDeterminant2x2)
		{
			std::array<std::array<double, 2>, 2> matr = { {
				{ 2, 7 },
				{ 6, 4 },
			} };
			auto actual = GetMatrixDeterminant(matr);

			double expected = -34;

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetMinor1)
		{
			matrix matr = { {
				{ 2, 5, 7 },
				{ 6, 3, 4 },
				{ 5, -2, -3 },
			} };
			auto actual = GetMinor(matr, 2, 1);

			double expected = -34;

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetMinor2)
		{
			matrix matr = { {
				{ 2, 5, 7 },
				{ 6, 3, 4 },
				{ 5, -2, -3 },
			} };
			auto actual = GetMinor(matr, 0, 0);

			double expected = -1;

			Assert::AreEqual(expected, actual);
		}
		
		TEST_METHOD(GetTransposedMatrix1)
		{
			matrix matr = {{
				{ 1, -2, 3 },
				{ 4, 0, 6 },
				{ -7, 8, 9 },
			}};
			auto actual = GetTransposedMatrix(matr);

			matrix expected = {{
				{ 1, 4, -7 },
				{ -2, 0, 8 },
				{ 3, 6, 9 },
			}};

			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(GetAlgebraicAdditionsMatrix1)
		{
			matrix matr = {{
				{ 2, 5, 7 },
				{ 6, 3, 4 },
				{ 5, -2, -3 },
			}};
			auto actual = GetAlgebraicAdditionsMatrix(matr);

			matrix expected = {{
				{ -1, 38, -27 },
				{ 1, -41, 29 },
				{ -1, 34, -24 },
			}};

			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(InvertWithDeterminantEqualTo0)
		{
			Assert::ExpectException<std::logic_error>([]() {
				matrix matr = { {
					{ 1, 1, 1 },
					{ 1, 1, 1 },
					{ 1, 1, 1 },
				} };
				InvertMatrix(matr);
			});
		}

		TEST_METHOD(Invert)
		{
			matrix matr = { {
				{ 2, 5, 7 },
				{ 6, 3, 4 },
				{ 5, -2, -3 },
			} };
			auto actual = InvertMatrix(matr);

			matrix expected = { {
				{ 1, -1, 1 },
				{ -38, 41, -34 },
				{ 27, -29, 24 },
			} };

			Assert::IsTrue(actual == expected);
		}
	};
}
