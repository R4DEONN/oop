#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <Windows.h>

using namespace std::string_literals;

using DictionaryType = std::map<std::string, std::vector<std::string>>;

enum class DictionaryStatus
{
	Reading,
	Writing
};

struct Args
{
	std::string dictionaryFileName;
};

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout
			<< "Incorrect arguments count" << std::endl
			<< "Usage: Dictionary.exe <dictionary file>" << std::endl;
		return std::nullopt;
	}

	return Args{ argv[1] };
}

DictionaryType GetDictionaryFromStream(std::istream& input)
{
	DictionaryType dictionary;

	std::string line;
	while (std::getline(input, line))
	{
		std::string word;
		input >> word;
		std::string key = word;
		std::vector<std::string> translations;
		while (input >> word)
		{
			translations.push_back(word);
		}

		dictionary.emplace(key, translations);
	}

	return dictionary;
}

DictionaryType GetDictionaryFromFile(const std::string& dictionaryFileName)
{
	std::ifstream input(dictionaryFileName);
	if (!input.is_open())
	{
		return {};
	}

	return GetDictionaryFromStream(input);
}

enum class ParseStatus
{

};

std::vector<std::string> GetWordsFromString(std::string& str)
{
	std::vector<std::string> words;
	std::string word;
	
    std::string token = std::strtok_s(str.data(), ",");
	while (!token.empty())
	{
		token.erase(std::remove_if(token.begin(), token.end(), ::isspace),
			token.end());
		words.push_back(token);
		token = std::strtok(nullptr, ",");
	}

	return words;
}

int main(int argc, char** argv)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	try
	{
		DictionaryType dictionary = GetDictionaryFromFile(args->dictionaryFileName);
		std::string line;
		auto status = DictionaryStatus::Reading;
		while (std::getline(std::cin, line) && line != "..."s)
		{
			switch (status)
			{
				case DictionaryStatus::Reading:
				if (auto it = dictionary.find(line);
					it != dictionary.end())
				{
					int translationsCount = dictionary[line].size();
					for (int i = 0; i < translationsCount; i++)
					{
						std::cout << dictionary[line][i];
						if (i != translationsCount - 1)
						{
							std::cout << ", ";
						}
					}
					std::cout << std::endl;
				}
				else
				{
					std::cout << "Ќеизвестное слово У" << line << "Ф. ¬ведите перевод или пустую строку дл€ отказа." << std::endl;
				}
					break;
				case DictionaryStatus::Writing:
					auto translations = GetWordsFromString(line);
					break;
			}
		}

		if (line == "..."s)
		{
			std::cout << "Changes have been made to the dictionary. Enter Y or y to save before exiting." << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}