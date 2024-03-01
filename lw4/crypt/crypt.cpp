#include <iostream>
#include <optional>
#include <string>
#include <fstream>

enum class CryptMode
{
	crypt,
	decrypt,
};

struct Args
{
	CryptMode cryptMode = CryptMode::crypt;
	std::string inputFileName;
	std::string outputFileName;
	int key = 0;
};

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 5)
	{
		std::cout
			<< "Invalid arguments count" << std::endl
			<< "Usage: crypt.exe <crypt|decrypt> <input file> <output file> <key>" << std::endl;
		return std::nullopt;
	}

	Args args;

	if (argv[1] == "crypt")
	{
		args.cryptMode = CryptMode::crypt;
	}
	else if (argv[1] == "decrypt")
	{
		args.cryptMode = CryptMode::decrypt;
	}
	else
	{
		std::cout
			<< "Invalid crypt mode" << std::endl
			<< "Usage: crypt.exe <crypt|decrypt> <input file> <output file> <key>" << std::endl;
		return std::nullopt;
	}

	try
	{
		int key = std::stoi(argv[4]);
		const int MIN_KEY_VALUE = 0;
		const int MAX_KEY_VALUE = 255;

		if (key < MIN_KEY_VALUE || key > MAX_KEY_VALUE)
		{
			std::cout << "The key must be in the range from 0 to 255" << std::endl;
			return std::nullopt;
		}

		args.key = key;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return std::nullopt;
	}


	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}

std::string CryptString(std::string str, int key)
{
	for (auto& ch : str)
	{
		ch ^= key;
		char result = 0b00000000;
		result |= (ch & 0b01100000) >> 5;
		result |= (ch & 0b00000111) << 2;
		result |= (ch & 0b10000000) >> 2;
		result |= (ch & 0b00011000) << 3;
		ch = result;
	}

	return str;
}

std::string DecryptString(std::string str, int key)
{
	for (auto& ch : str)
	{
		char result = 0b00000000;
		result |= (ch & 0b00000011) << 5;
		result |= (ch & 0b00011100) >> 2;
		result |= (ch & 0b00100000) << 2;
		result |= (ch & 0b11000000) >> 3;
		ch = result;
		ch ^= key;
	}

	return str;
}

void CopyFileWithCrypt(
	CryptMode mode,
	const std::string& inputFileName,
	const std::string& outputFileName,
	int key
) {
	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		throw std::ifstream::failure("Failed to open '" + inputFileName + "'");
	}

	std::ofstream output(outputFileName);
	if (!output.is_open())
	{
		throw std::ofstream::failure("Failed to open '" + outputFileName + "'");
	}

	std::string line;
	while (std::getline(input, line))
	{
		if (output)
		{
			switch (mode)
			{
			case CryptMode::crypt:
				output << CryptString(line, key) << std::endl;
				break;
			case CryptMode::decrypt:
				output << DecryptString(line, key) << std::endl;
				break;
			}
		}
		else
		{
			throw std::ofstream::failure("Failed to writing in " + outputFileName);
		}
	}

	if (!input.eof())
	{
		throw std::ifstream::failure("Failed to reading '" + inputFileName + "'");
	}
}

int main(int argc, char** argv)
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	try
	{
		CopyFileWithCrypt(
			args->cryptMode,
			args->inputFileName,
			args->outputFileName,
			args->key
		);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}