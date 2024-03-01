#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

const constexpr int MATRIX_DIM = 3;

using matrixLine = std::array<double, MATRIX_DIM>;
using matrix = std::array<matrixLine, MATRIX_DIM>;

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

	if (i < MATRIX_DIM)
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

	return GetMatrixFromStream(input);
}

double GetMatrixDeterminant(const matrix& matr)
{
	return matr[0][0] * matr[1][1] * matr[2][2] - matr[0][0] * matr[1][2] * matr[2][1]
		- matr[0][1] * matr[1][0] * matr[2][2] + matr[0][1] * matr[1][2] * matr[2][0]
		+ matr[0][2] * matr[1][0] * matr[2][1] - matr[0][2] * matr[1][1] * matr[2][0];
}

double GetMatrixDeterminant(const std::array<std::array<double, 2>, 2>& matr)
{
	return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
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
	std::array<std::array<double, 2>, 2> newMatr;

    int newRow = 0;
	for (int i = 0; i < MATRIX_DIM; ++i)
	{
		if (i == line)
		{
			continue;
		}

		int newColumn = 0;
		for (int j = 0; j < MATRIX_DIM; ++j)
		{
			if (j == column)
			{
				continue;
			}
			newMatr[newRow][newColumn] = matr[i][j];
			++newColumn;
		}
		++newRow;
	}

	return GetMatrixDeterminant(newMatr);
}

matrix GetCofactorsMatrix(const matrix& matr)
{
	matrix cofactorsMatrix;
	for (int i = 0; i < MATRIX_DIM; i++)
	{
		for (int j = 0; j < MATRIX_DIM; j++)
		{
			cofactorsMatrix[i][j] = GetMinor(matr, i, j);
		}
	}

	cofactorsMatrix[0][1] *= -1;
	cofactorsMatrix[1][0] *= -1;
	cofactorsMatrix[1][2] *= -1;
	cofactorsMatrix[2][1] *= -1;

	return cofactorsMatrix;
}

void ScaleMatrix(matrix& matr, float scale)
{
	for (auto& matrixLine : matr)
	{
		for (auto& matrixElement : matrixLine)
		{
			matrixElement *= scale;
		}
	}
}

std::optional<matrix> InvertMatrix(const matrix& originalMatrix)
{
	auto determinant = GetMatrixDeterminant(originalMatrix);

	if (determinant == 0)
	{
		throw std::logic_error("It is impossible to find the inverse matrix, since its determinant is 0");
		return std::nullopt;
	}

	auto cofactorsMatrix = GetCofactorsMatrix(originalMatrix);
	auto transposedMatrix = GetTransposedMatrix(cofactorsMatrix);
	auto inverseDeterminant = 1 / determinant;

	ScaleMatrix(transposedMatrix, inverseDeterminant);

	return transposedMatrix;
}

void PrintMatrix(const matrix& matr)
{
	std::cout.precision(2);
	for (auto& matrixLine : matr)
	{
		for (auto matrixElement : matrixLine)
		{
			std::cout << matrixElement << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
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
		matrix originalMatrix = GetMatrixFromFile(args->inputFileName);
		auto inverseMatrix = InvertMatrix(originalMatrix);
		if (!inverseMatrix)
		{
			throw std::invalid_argument("It is impossible to invert the matrix");
		}
		PrintMatrix(*inverseMatrix);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}