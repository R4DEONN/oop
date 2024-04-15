#include <iostream>
#include "primes.h"
#include <string>

struct Args
{
	int upperBound;
};

Args ParseArgs(int argc, char** argv)
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid arguments count\nUsage: primes.cpp <upper bound>");
	}

	Args args;
	args.upperBound = std::stoi(argv[1]);

	return args;
}

void PrintSet(const std::set<int> set)
{
	for (auto element : set)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	try
	{
		auto args = ParseArgs(argc, argv);
		auto primes = GeneratePrimeNumbersSet(args.upperBound);
		std::cout << "Primes: ";
		PrintSet(primes);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}