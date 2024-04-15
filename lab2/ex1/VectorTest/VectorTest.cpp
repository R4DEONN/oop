#include "pch.h"
#include "CppUnitTest.h"
#include "../vector/vector.cpp"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool IsDoublesEqual(double x, double y)
{
	return std::abs(x - y) < std::numeric_limits<double>::epsilon();
}

bool IsVectorsEqual(const std::vector<double> vector1, const std::vector<double> vector2)
{
	for (int i = 0; i < vector1.size(); i++)
	{
		if (!IsDoublesEqual(vector1[i], vector2[i]))
		{
			return false;
		}
	}

	return true;
}

namespace VectorTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		
		TEST_METHOD(GetVectorFromInput)
		{
			std::stringstream stream("1.5 5 5.2 6 7");

			auto actual = GetVectorFromStream(stream);
			std::vector<double> expected = { 1.5, 5, 5.2, 6, 7 };

			Assert::IsTrue(IsVectorsEqual(actual, expected));
		}
		
		TEST_METHOD(GetVectorFromNullableStream)
		{
			std::stringstream stream(" ");

			auto actual = GetVectorFromStream(stream);
			std::vector<double> expected;

			Assert::IsTrue(IsVectorsEqual(actual, expected));
		}

		TEST_METHOD(GetVectorFromStreamWithLetters)
		{
			std::stringstream stream("a b c");

			auto actual = GetVectorFromStream(stream);
			std::vector<double> expected;

			Assert::IsTrue(IsVectorsEqual(actual, expected));
		}

		TEST_METHOD(SubtractMedianFromEvenCountOfElements)
		{
			std::vector<double> actual = { 1.5, 5, 6, 7 };

			SubtractMedianFromElements(actual);
			std::vector<double> expected = { -4, -0.5, 0.5, 1.5 };

			Assert::IsTrue(IsVectorsEqual(actual, expected));
		}

		TEST_METHOD(SubtractMedianFromOddCountOfElements)
		{
			std::vector<double> actual = { 1.5, 5, 4.8, 6, 7 };

			SubtractMedianFromElements(actual);
			std::vector<double> expected = { -3.5, 0, -0.2, 1, 2 };

			Assert::IsTrue(IsVectorsEqual(actual, expected));
		}

		TEST_METHOD(SubtractMedianFromEmptyVector)
		{
			std::vector<double> actual;

			SubtractMedianFromElements(actual);
			std::vector<double> expected;

			Assert::IsTrue(IsVectorsEqual(actual, expected));
		}
	};
}
