#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 5)
	{
		std::cout
			<< "Invalid argument count" << std::endl
			<< "Usage: Replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
		return std::nullopt;
	}

	if (argv[1] == argv[2])
	{
		std::cout << "Input and output files must be different" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;

	while (pos != std::string::npos)
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			break;
		}
		else
		{
			result += replacementString;
			pos = foundPos + searchString.length();
		}
	}
	return result;
}

void CopyFileWithReplacement(
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& searchString,
	const std::string& replacementString)
{
	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		const std::string exceptionMessage = "Failed to open '" + inputFileName + "' for reading";
		throw std::ifstream::failure(exceptionMessage);
	}

	std::ofstream output(outputFileName);
	if (!output.is_open())
	{
		const std::string exceptionMessage = "Failed to open '" + outputFileName + "' for writing";
		throw std::ofstream::failure(exceptionMessage);
	}

	std::string line;
	while (std::getline(input, line))
	{
		if (output)
		{
			output << ReplaceString(line, searchString, replacementString) << std::endl;
		}
		else
		{
			throw std::ofstream::failure("Failed to writing in " + outputFileName);
		}
	}
	
	if (!input.good())
	{
		throw std::ifstream::failure("Failed to reading " + inputFileName);
	}
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
		CopyFileWithReplacement(
			args->inputFileName,
			args->outputFileName,
			args->searchString,
			args->replaceString);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
