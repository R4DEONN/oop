#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

using namespace std::string_literals;

//TODO: Coding_Conventions
enum class CryptMode
{
	Crypt,
	Decrypt,
};

struct Args
{
	CryptMode cryptMode = CryptMode::Crypt;
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

	std::string command = argv[1];
	
	if (command == "crypt")
	{
		args.cryptMode = CryptMode::Crypt;
	}
	else if (command == "decrypt")
	{
		args.cryptMode = CryptMode::Decrypt;
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
		constexpr int MIN_KEY_VALUE = 0;
		constexpr int MAX_KEY_VALUE = 255;

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

//TODO: Выделить независимый модуль
char CryptChar(char ch, int key)
{
	ch ^= key;
	//TODO Тесты с двоичным числом
	char result = 0b00000000;
	result |= (ch & 0b01100000) >> 5;
	result |= (ch & 0b00000111) << 2;
	result |= (ch & 0b10000000) >> 2;
	result |= (ch & 0b00011000) << 3;
	return result;
}

char DecryptChar(char ch, int key)
{
	char result = 0b00000000;
	result |= (ch & 0b00000011) << 5;
	result |= (ch & 0b00011100) >> 2;
	result |= (ch & 0b00100000) << 2;
	result |= (ch & 0b11000000) >> 3;
	ch = result;
	ch ^= key;
	return ch;
}

void CopyFileWithCrypt(
	CryptMode mode,
	const std::string& inputFileName,
	const std::string& outputFileName,
	int key)
{
	std::ifstream input(inputFileName, std::ios::binary);
	if (!input.is_open())
	{
		throw std::ifstream::failure("Failed to open '" + inputFileName + "'");
	}

	std::ofstream output(outputFileName, std::ios::binary);
	if (!output.is_open())
	{
		throw std::ofstream::failure("Failed to open '" + outputFileName + "'");
	}

	std::transform(std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(output),
		[&](char ch) {
			switch (mode)
			{
			case CryptMode::Crypt:
				return CryptChar(ch, key);
			case CryptMode::Decrypt:
				return DecryptChar(ch, key);
			}
		});

	//TODO Разобраться, что такое flush
	if (input.bad())
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
			args->key);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}