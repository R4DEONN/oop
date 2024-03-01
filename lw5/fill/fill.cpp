#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <queue>

enum struct CellType
{
	Null = 0,
	Border,
	StartPoint,
};

using matrixLine = std::vector<int>;
using matrix = std::vector<matrixLine>;

struct Point
{
	int x;
	int y;
};

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout
			<< "Invalid arguments count" << std::endl
			<< "fill.exe <input file> <output file>" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

struct ParseData
{
	matrix matr;
	std::vector<Point> startPoints;
};

void FillMatrixWithSpace(matrix& matr, int lineLength)
{
	for (auto& matrixRow : matr)
	{
		matrixRow.resize(lineLength, 0);
	}
}

ParseData ParseFile(std::istream& input)
{
	std::vector<Point> startPoints;

	constexpr const int fillSize = 100;
	matrix matr;
	std::string line;
	int maxLineLength = 0;

	for (int i = 0; std::getline(input, line) && i < fillSize; i++)
	{
		if (line.size() > maxLineLength)
		{
			maxLineLength = static_cast<int>(line.size());
		}
		matrixLine matrLine;

		for (int j = 0; j < fillSize && j < line.size(); j++)
		{
			switch (line[j])
			{
			case ' ':
				matrLine.push_back(static_cast<int>(CellType::Null));
				continue;
			case 'O':
				matrLine.push_back(static_cast<int>(CellType::StartPoint));
				startPoints.emplace_back(j, i);
				continue;
			case '#':
				matrLine.push_back(static_cast<int>(CellType::Border));
			}
		}

		matr.push_back(matrLine);
	}

	FillMatrixWithSpace(matr, maxLineLength);

	if (!input.eof())
	{
		throw std::ifstream::failure("Failed to reading input file");
	}

	return {matr, startPoints};
}

void FillMatrix(matrix& matr, const std::vector<Point> startPoints)
{
	std::queue<Point> queue;
	for (auto [x, y] : startPoints)
	{
		queue.emplace(x, y);
	}

	while (!queue.empty())
	{
		auto [x, y] = queue.front();
		queue.pop();

		if (y - 1 >= 0 && matr[y - 1][x] == 0)
		{
			queue.emplace(x, y - 1);
			matr[y - 1][x] = 3;
		}

		if (x - 1 >= 0 && matr[y][x - 1] == 0)
		{
			queue.emplace(x - 1, y);
			matr[y][x - 1] = 3;
		}

		if (y + 1 < matr.size() && matr[y + 1][x] == 0)
		{
			queue.emplace(x, y + 1);
			matr[y + 1][x] = 3;
		}

		if (x + 1 < matr[y].size() && matr[y][x + 1] == 0)
		{
			queue.emplace(x + 1, y);
			matr[y][x + 1] = 3;
		}
	}
}

void CopyFileWithFill(const std::string& inputFileName, const std::string& outputFileName)
{
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

	auto parseData = ParseFile(input);
	FillMatrix(parseData.matr, parseData.startPoints);

	for (auto& line : parseData.matr)
	{
		for (auto element : line)
		{
			switch (element)
			{
			case 0:
				output << ' ';
				continue;
			case 1:
				output << '#';
				continue;
			case 2:
				output << 'O';
				continue;
			case 3:
				output << '.';
			}
		}
		output << std::endl;
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
		CopyFileWithFill(args->inputFileName, args->outputFileName);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}