#include "pch.h"
#include "CppUnitTest.h"
#include "../Radix/Radix.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RadixTest
{
	TEST_CLASS(RadixTest)
	{
	public:
		
		TEST_METHOD(Char0ToInt)
		{
			int result = CharToInt('0');
			int expected = 0;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(CharZToInt)
		{
			int result = CharToInt('Z');
			int expected = 35;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(UnknownCharToInt)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				CharToInt('Ü');
			});
		}

		TEST_METHOD(String10ToInt)
		{
			auto radix = 10;
			std::string str = "10";
			int result = StringToInt(str, radix);
			int expected = 10;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(StringWithUnknownCharacterToInt)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				auto wasError = false;
				auto radix = 10;
				std::string str = "1Ü";
				int result = StringToInt(str, radix);
			});
		}

		TEST_METHOD(NegativeStringToInt)
		{
			auto radix = 10;
			std::string str = "-10";
			int result = StringToInt(str, radix);
			int expected = -10;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(StringIn2RadixToInt)
		{
			auto radix = 2;
			std::string str = "1010";
			int result = StringToInt(str, radix);
			int expected = 10;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(StringIn35RadixToInt)
		{
			auto radix = 36;
			std::string str = "1Z";
			int result = StringToInt(str, radix);
			int expected = 71;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IntMaxStringRadixToInt)
		{
			auto radix = 10;
			std::string str = "2147483647";
			int result = StringToInt(str, radix);
			int expected = INT_MAX;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IntMinStringRadixToInt)
		{
			auto radix = 10;
			std::string str = "-2147483648";
			int result = StringToInt(str, radix);
			int expected = INT_MIN;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(NegativeOverflowStringRadixToInt)
		{
			Assert::ExpectException<std::overflow_error>([]() {
				auto radix = 10;
				std::string str = "-2147483649";
				int result = StringToInt(str, radix);
			});
		}

		TEST_METHOD(PositiveOverflowStringRadixToInt)
		{
			Assert::ExpectException<std::overflow_error>([]() {
				auto radix = 10;
				std::string str = "2147483648";
				int result = StringToInt(str, radix);
			});
		}

		TEST_METHOD(Int10ToString)
		{
			auto radix = 10;
			int number = 10;
			std::string actual = IntToString(number, radix);
			std::string expected = "10";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(NegativeInt10ToString)
		{
			auto radix = 10;
			int number = -10;
			std::string actual = IntToString(number, radix);
			std::string expected = "-10";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Radix36IntToString)
		{
			auto radix = 36;
			int number = 71;
			std::string actual = IntToString(number, radix);
			std::string expected = "1Z";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestination)
		{
			int sourceNotation = 16;
			int destinationNotation = 10;
			std::string value = "1F";
			std::string actual = ConvertNotation(
				sourceNotation,
				destinationNotation,
				value
			);
			std::string expected = "31";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestinationUnknownCharacter)
		{
			int sourceNotation = 16;
			int destinationNotation = 10;
			std::string value = "1Ü";

			Assert::ExpectException<std::logic_error>([
				sourceNotation,
				destinationNotation,
				value
			]() {
				ConvertNotation(
					sourceNotation,
					destinationNotation,
					value
				);
			});
		}

		TEST_METHOD(TranslateSourceToDestinationINTMAX)
		{
			int sourceNotation = 10;
			int destinationNotation = 36;
			std::string value = "2147483647";
			std::string actual = ConvertNotation(
				sourceNotation,
				destinationNotation,
				value);
			std::string expected = "ZIK0ZJ";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestinationINTMIN)
		{
			int sourceNotation = 10;
			int destinationNotation = 2;
			std::string value = "-2147483648";
			std::string actual = ConvertNotation(
				sourceNotation,
				destinationNotation,
				value);
			std::string expected = "-10000000000000000000000000000000";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestinationOverflow)
		{
			int sourceNotation = 10;
			int destinationNotation = 2;
			std::string value = "-2147483649000000";

			Assert::ExpectException<std::overflow_error>([
				sourceNotation,
				destinationNotation,
				value
			]() {
				ConvertNotation(sourceNotation, destinationNotation, value);
			});
		}
	};
}
