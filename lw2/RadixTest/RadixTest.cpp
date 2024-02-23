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
			auto wasError = false;
			auto radix = 10;
			std::string str = "10";
			int result = StringToInt(str, radix, wasError);
			int expected = 10;

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(StringWithUnknownCharacterToInt)
		{
			auto wasError = false;
			auto radix = 10;
			std::string str = "1Ü";
			int result = StringToInt(str, radix, wasError);

			Assert::IsTrue(wasError);
		}

		TEST_METHOD(NegativeStringToInt)
		{
			auto wasError = false;
			auto radix = 10;
			std::string str = "-10";
			int result = StringToInt(str, radix, wasError);
			int expected = -10;

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(StringIn2RadixToInt)
		{
			auto wasError = false;
			auto radix = 2;
			std::string str = "1010";
			int result = StringToInt(str, radix, wasError);
			int expected = 10;

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(StringIn35RadixToInt)
		{
			auto wasError = false;
			auto radix = 36;
			std::string str = "1Z";
			int result = StringToInt(str, radix, wasError);
			int expected = 71;

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IntMaxStringRadixToInt)
		{
			auto wasError = false;
			auto radix = 10;
			std::string str = "2147483647";
			int result = StringToInt(str, radix, wasError);
			int expected = INT_MAX;

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IntMinStringRadixToInt)
		{
			auto wasError = false;
			auto radix = 10;
			std::string str = "-2147483648";
			int result = StringToInt(str, radix, wasError);
			int expected = INT_MIN;

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(NegativeOverflowStringRadixToInt)
		{
			auto wasError = false;
			auto radix = 10;
			std::string str = "-2147483649";
			int result = StringToInt(str, radix, wasError);

			Assert::IsTrue(wasError);
		}

		TEST_METHOD(PositiveOverflowStringRadixToInt)
		{
			auto wasError = false;
			auto radix = 10;
			std::string str = "2147483648";
			int result = StringToInt(str, radix, wasError);

			Assert::IsTrue(wasError);
		}

		TEST_METHOD(Int10ToString)
		{
			auto wasError = false;
			auto radix = 10;
			int number = 10;
			std::string actual = IntToString(number, radix, wasError);
			std::string expected = "10";

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(NegativeInt10ToString)
		{
			auto wasError = false;
			auto radix = 10;
			int number = -10;
			std::string actual = IntToString(number, radix, wasError);
			std::string expected = "-10";

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Radix36IntToString)
		{
			auto wasError = false;
			auto radix = 36;
			int number = 71;
			std::string actual = IntToString(number, radix, wasError);
			std::string expected = "1Z";

			Assert::IsFalse(wasError);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestination)
		{
			std::string sourceNotation = "16";
			std::string destinationNotation = "10";
			std::string value = "1F";
			std::string actual = TranslateSourceNotationToDestinationNotation(
				sourceNotation,
				destinationNotation,
				value
			);
			std::string expected = "31";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestinationUnknownCharacter)
		{
			std::string sourceNotation = "16";
			std::string destinationNotation = "10";
			std::string value = "1Ü";

			Assert::ExpectException<std::logic_error>([
				sourceNotation,
				destinationNotation,
				value
			]() {
				TranslateSourceNotationToDestinationNotation(
					sourceNotation,
					destinationNotation,
					value
				);
			});
		}

		TEST_METHOD(TranslateSourceToDestinationINTMAX)
		{
			std::string sourceNotation = "10";
			std::string destinationNotation = "36";
			std::string value = "2147483647";
			std::string actual = TranslateSourceNotationToDestinationNotation(
				sourceNotation,
				destinationNotation,
				value);
			std::string expected = "ZIK0ZJ";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestinationINTMIN)
		{
			std::string sourceNotation = "10";
			std::string destinationNotation = "2";
			std::string value = "-2147483648";
			std::string actual = TranslateSourceNotationToDestinationNotation(
				sourceNotation,
				destinationNotation,
				value);
			std::string expected = "-10000000000000000000000000000000";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TranslateSourceToDestinationOverflow)
		{
			std::string sourceNotation = "10";
			std::string destinationNotation = "2";
			std::string value = "-2147483649000000";

			Assert::ExpectException<std::logic_error>([
				sourceNotation,
				destinationNotation,
				value
			]() {
				TranslateSourceNotationToDestinationNotation(sourceNotation, destinationNotation, value);
			});
		}
	};
}
