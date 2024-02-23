#include <iostream>
#include <optional>
#include <array>
#include <string>
#include <fstream>
#include <sstream>

const constexpr int MATRIX_DIM = 3;

typedef std::array<double, MATRIX_DIM> matrixLine;
typedef std::array<matrixLine, MATRIX_DIM> matrix;


struct Args
{
	std::string inputFileName;
};

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout
			<< "Invalid argument count" << std::endl
			<< "Usage: invert.exe <matrix file>" << std::endl;
		return std::nullopt;
	}

	return Args{ argv[1] };
}

matrix GetMatrixFromStream(std::istream& input)
{
	matrix matrixFromStream;
	int i = 0;
	std::string line;
	while (std::getline(input, line))
	{
		std::stringstream strstream(line);
		matrixLine matrixLine;
		for (int j = 0; j < MATRIX_DIM; j++)
		{
			strstream >> matrixLine[j];
		}
		matrixFromStream[i] = matrixLine;
		i++;
		if (i == MATRIX_DIM)
		{
			break;
		}
	}

	if (i < 3)
	{
		throw std::logic_error("The dimension of the matrix should be 3x3");
	}

	if (!input.good())
	{
		throw std::ifstream::failure("Failed to reading input file");
	}

	return matrixFromStream;
}

matrix GetMatrixFromFile(const std::string& inputFileName)
{
	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		throw std::ifstream::failure("Failed to open '" + inputFileName + "' for reading");
	}

	matrix matrixFromFile;
	try
	{
		matrixFromFile = GetMatrixFromStream(input);
	}
	catch (const std::exception& e)
	{
		throw;
	}

	return matrixFromFile;
}

template <typename T>
double GetMatrixDeterminant(const T& matr)
{
	int dim = matr.size();
	if (dim == 2)
	{
		return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
	}
	else if (dim == 3)
	{
		return matr[0][0] * matr[1][1] * matr[2][2] - matr[0][0] * matr[1][2] * matr[2][1]
			- matr[0][1] * matr[1][0] * matr[2][2] + matr[0][1] * matr[1][2] * matr[2][0]
			+ matr[0][2] * matr[1][0] * matr[2][1] - matr[0][2] * matr[1][1] * matr[2][0];
	}

	return 0;
}

matrix GetTransposedMatrix(matrix matr)
{
	double tmp;
	for (int i = 0; i < MATRIX_DIM; ++i)
	{
		for (int j = i; j < MATRIX_DIM; ++j)
		{
			tmp = matr[i][j];
			matr[i][j] = matr[j][i];
			matr[j][i] = tmp;
		}
	}

	return matr;
}

double GetMinor(const matrix& matr, int line, int column)
{
	int topLine = std::min((line + 1) % 3, (line + 2) % 3);
	int leftColumn = std::min((column + 1) % 3, (column + 2) % 3);
	int bottomLine = std::max((line + 1) % 3, (line + 2) % 3);
	int rightColumn = std::max((column + 1) % 3, (column + 2) % 3);
	std::array<std::array<double, 2>, 2> newMatr = {{
		{ matr[topLine][leftColumn], matr[topLine][rightColumn] },
		{ matr[bottomLine][leftColumn], matr[bottomLine][rightColumn] },
	}};

	return GetMatrixDeterminant(newMatr);
}

matrix GetAlgebraicAdditionsMatrix(const matrix& matr)
{
	matrix algebraicAdditionsMatrix;
	for (int i = 0; i < MATRIX_DIM; i++)
	{
		for (int j = 0; j < MATRIX_DIM; j++)
		{
			algebraicAdditionsMatrix[i][j] = GetMinor(matr, i, j);
		}
	}

	algebraicAdditionsMatrix[0][1] *= -1;
	algebraicAdditionsMatrix[1][0] *= -1;
	algebraicAdditionsMatrix[1][2] *= -1;
	algebraicAdditionsMatrix[2][1] *= -1;

	return algebraicAdditionsMatrix;
}

matrix InvertMatrix(const matrix& originalMatrix)
{
	auto determinant = GetMatrixDeterminant(originalMatrix);

	if (determinant == 0)
	{
		throw std::logic_error("It is impossible to find the inverse matrix, since its determinant is 0");
	}

	auto algebraicAdditionsMatrix = GetAlgebraicAdditionsMatrix(originalMatrix);
	auto transposedMatrix = GetTransposedMatrix(algebraicAdditionsMatrix);
	auto inverseDeterminant = 1/determinant;

	for (auto& matrixLine : transposedMatrix)
	{
		for (auto& matrixElement : matrixLine)
		{
			matrixElement *= inverseDeterminant;
		}
	}

	return transposedMatrix;
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
		matrix originalMatrix = GetMatrixFromFile(args->inputFileName);
		auto inverseMatrix = InvertMatrix(originalMatrix);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}