#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

enum struct CellType
{
	Null = ' ',
	Border = '#',
	StartPoint = 'O',
	FillPoint = '.',
};


struct Cell
{
	CellType type;

	Cell(char c)
		: type(static_cast<CellType>(c))
	{
	}

	Cell(CellType type)
		: type(type)
	{
	}

	operator char() const
	{
		return static_cast<char>(type);
	}
};

using matrixLine = std::vector<Cell>;
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
		matrixRow.resize(lineLength, Cell{ CellType::Null });
	}
}

ParseData ParseFile(std::istream& input)
{
	std::vector<Point> startPoints;
	matrix matr;
	std::string line;
	constexpr const int fillSize = 100;
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
				matrLine.push_back(Cell{ CellType::Null });
				continue;
			case 'O':
				matrLine.push_back(Cell{ CellType::StartPoint });
				startPoints.emplace_back(j, i);
				continue;
			case '#':
				matrLine.push_back(Cell{ CellType::Border });
			}
		}

		matr.push_back(matrLine);
	}

	FillMatrixWithSpace(matr, maxLineLength);

	return {matr, startPoints};
}

void FillAdjacentCell(matrix& matr, int x, int y, std::queue<Point>& queue)
{
	int dx[] = { 0, -1, 0, 1 };
	int dy[] = { -1, 0, 1, 0 };

	for (int i = 0; i < 4; ++i)
	{
		int newX = x + dx[i];
		int newY = y + dy[i];

		if (newX >= 0 && newY >= 0
			&& newY < matr.size() && newX < matr[newY].size()
			&& matr[newY][newX] == Cell{ CellType::Null }
		) {
			queue.emplace(newX, newY);
			matr[newY][newX] = Cell{ CellType::FillPoint };
		}
	}
}

void FillMatrix(matrix& matr, const std::vector<Point> startPoints)
{
	//TODO вы€снить, что быстрее очередь или стек: ќчередь дл€ 100x100 стек за 0.008, очередб за 0.005
	std::queue<Point> queue;
	for (auto [x, y] : startPoints)
	{
		queue.emplace(x, y);
	}

	while (!queue.empty())
	{
		auto [x, y] = queue.front();
		queue.pop();

		FillAdjacentCell(matr, x, y, queue);
	}
}

void FillFileToFile(const std::string& inputFileName, const std::string& outputFileName)
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
			output << element;
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
		FillFileToFile(args->inputFileName, args->outputFileName);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}