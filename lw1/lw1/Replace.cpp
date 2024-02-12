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
		return std::nullopt;
	}

	if (argv[1] == argv[2])
	{
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

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, subject.length() - pos);
			break;
		}
		else
		{
			result.append(subject, pos, foundPos - pos);
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
	}
	return result;
}

void CopyFileWithReplacement(
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& searchString,
	const std::string& replaceString)
{
	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		const std::string exceptionMessage = "Failed to open '" + inputFileName + "' for reading";
		throw std::logic_error(exceptionMessage);
	}

	std::ofstream output(outputFileName);
	if (!output.is_open())
	{
		const std::string exceptionMessage = "Failed to open '" + outputFileName + "' for writing";
		throw std::logic_error(exceptionMessage);
	}

	for (std::string line; std::getline(input, line);)
	{
		output << ReplaceString(line, searchString, replaceString) << "\n";
	}
}

int main(int argc, char** argv)
{

	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Invalid argument\n";
		std::cout << "Usage: Replace.exe <input file> <output file> <search string> <replace string>\n";
		std::cout << "Input and output files must be different\n";
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
		throw;
	}

	return EXIT_SUCCESS;
}
