#include <iostream>
#include <optional>
#include <string>

const int CHAR_OFFSET = 10;

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

int CharToInt(char ch)
{
	int charByte = static_cast<int>(ch);
	int number = charByte >= 'A' ? charByte -= 'A' - CHAR_OFFSET : charByte -= '0';

	const int MIN_NUMBER = 0;
	const int MAX_NUMBER = 35;

	if (number < MIN_NUMBER || number > MAX_NUMBER)
	{
		std::string exceptionMessage = "The number is entered in the wrong format. Unknown character " + ch;
		throw std::invalid_argument(exceptionMessage);
	}

	return number;
}

int StringToInt(const std::string& str, int radix)
{
	int accumulator = 0;

	bool isNegative = false;
	if (str[0] == '-')
	{
		isNegative = true;
	}

	const int MAX_RADIX = 36;
	const int MIN_RADIX = 2;
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		throw std::invalid_argument("Wrong notation: " + radix);
	}

	for (int i = isNegative; i < str.length(); i++)
	{
		auto ch = str[i];
		int unit = CharToInt(ch);
		if ((!isNegative && (INT_MAX - unit) / radix >= accumulator)
			|| (isNegative && (INT_MIN + unit) / radix <= accumulator))
		{
			accumulator *= radix;
			accumulator = isNegative ? accumulator - unit : accumulator + unit;
		}
		else
		{
			throw std::overflow_error("There was an overflow during the translate");
		}
	}

	return accumulator;
}

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cout
			<< "Invalid argument count" << std::endl
			<< "Usage: Radix.exe <source notation> <destination notation> <value>" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.sourceNotation = StringToInt(argv[1], 10);
	args.destinationNotation = StringToInt(argv[2], 10);
	args.value = argv[3];

	return args;
}

char UnitToChar(int unit)
{
	unit > 9 ? unit += 'A' - CHAR_OFFSET : unit += '0';
	char ch = static_cast<char>(unit);

	return ch;
}

std::string IntToString(int number, int radix)
{
	if (number == 0)
	{
		return "0";
	}

	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
	}

	std::string result;
	do
	{
		int unit = number % radix;
		if (isNegative)
		{
			unit *= -1;
		}
		result = UnitToChar(unit) + result;
		number /= radix;
	} while (number != 0);

	return isNegative ? "-" + result : result;
}

std::string ConvertNotation(
	int sourceRadix,
	int destinationRadix,
	const std::string& value)
{
	int integerValue = StringToInt(value, sourceRadix);
	std::string valueInDestinationNotation = IntToString(integerValue, destinationRadix);

	return valueInDestinationNotation;
}

int main(int argc, char** argv)
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_SUCCESS;
	}

	try
	{
		auto destinationNotationValue = ConvertNotation(
			args->sourceNotation,
			args->destinationNotation,
			args->value);

		std::cout << "Number in destination notation: " << destinationNotationValue << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}