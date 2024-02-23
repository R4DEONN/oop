#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

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
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];

	return args;
}

int CharToInt(char ch)
{
	int number = static_cast<int>(ch) - 48;
	if (number > 9)
	{
		number -= 7;
	}

	const int MIN_NUMBER = 0;
	const int MAX_NUMBER = 35;

	if (number < MIN_NUMBER || number > MAX_NUMBER)
	{
		std::string exceptionMessage = "The number is entered in the wrong format. Unknown character " + ch;
		throw std::invalid_argument(exceptionMessage);
	}

	return number;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int accumulator = 0;

	bool isNegative = false;
	if (str[0] == '-')
	{
		isNegative = true;
	}

	try
	{
		if (radix < 2 || radix > 36)
		{
			throw std::invalid_argument("Wrong notation: " + radix);
		}

		for (int i = isNegative; i < str.length(); i++)
		{
			auto ch = str[i];
			int unit = CharToInt(ch);
			if ((!isNegative && INT_MAX - unit >= accumulator * radix)
				|| (isNegative && INT_MIN + unit <= accumulator * radix))
			{
				accumulator *= radix;
				accumulator = isNegative ? accumulator - unit : accumulator + unit;
			}
			else
			{
				throw std::logic_error("There was an overflow during the translate");
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		wasError = true;
	}

	return accumulator;
}

char UnitToChar(int unit)
{
	if (unit > 9)
	{
		unit += 7;
	}
	char ch = static_cast<char>(unit + 48);

	return ch;
}

std::string IntToString(int number, int radix, bool& wasError)
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

std::string TranslateSourceNotationToDestinationNotation(
	const std::string& sourceNotation,
	const std::string& destinationNotation,
	const std::string& value)
{
	bool wasError = false;
	int sourceRadix = StringToInt(sourceNotation, 10, wasError);
	int destinationRadix = StringToInt(destinationNotation, 10, wasError);
	int integerValue = StringToInt(value, sourceRadix, wasError);
	std::string valueInDestinationNotation = IntToString(integerValue, destinationRadix, wasError);

	if (wasError)
	{
		throw std::logic_error("Error during translate process");
	}

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
		auto destinationNotationValue = TranslateSourceNotationToDestinationNotation(
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