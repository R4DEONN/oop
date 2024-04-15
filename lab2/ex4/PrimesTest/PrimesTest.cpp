#include "pch.h"
#include "CppUnitTest.h"
#include "../primes/primes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PrimesTest
{
	TEST_CLASS(PrimesTest)
	{
	public:
		
		TEST_METHOD(GeneratePrimeNumbersSetOf10)
		{
			auto actual = GeneratePrimeNumbersSet(10);
			std::set<int> expected = {2, 3, 5, 7};

			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(GeneratePrimeNumbersSetOf2)
		{
			auto actual = GeneratePrimeNumbersSet(2);
			std::set<int> expected = { 2 };

			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(GeneratePrimeNumbersSetOfMaxBound)
		{
			auto actual = GeneratePrimeNumbersSet(MaxUpperBound);

			Assert::AreEqual(actual.size(), static_cast<size_t>(5761455));
		}

		TEST_METHOD(GeneratePrimeNumbersSetOfZero)
		{
			Assert::ExpectException<std::invalid_argument>(
				[]() {
					GeneratePrimeNumbersSet(0);
				}
			);
		}

		TEST_METHOD(GeneratePrimeNumbersSetOfOverflow)
		{
			Assert::ExpectException<std::invalid_argument>(
				[]() {
					GeneratePrimeNumbersSet(MaxUpperBound + 1);
				});
		}
	};
}
