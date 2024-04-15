#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<double> GetVectorFromStream(std::istream& input)
{
	std::vector<double> vector(std::istream_iterator<double>(input), (std::istream_iterator<double>()));;
	return vector;
}

void SubtractMedianFromElements(std::vector<double>& vector)
{
	if (vector.empty())
	{
		return;
	}

	auto copyVector = vector;
	auto medianIndex = vector.size() / 2;
	std::nth_element(copyVector.begin(), copyVector.begin() + medianIndex, copyVector.end());

	double median = 0;
	if (vector.size() % 2 == 0)
	{
		median = (copyVector[medianIndex - 1] + copyVector[medianIndex]) / 2;
	}
	else
	{
		median = copyVector[medianIndex];
	}

	std::transform(vector.begin(), vector.end(), vector.begin(),
		[median](double el) { return el - median; }
	);
}

void PrintVector(const std::vector<double>& vector)
{
	for (auto num : vector)
	{
		std::cout << std::fixed << std::setprecision(2) << num << " ";
	}

	std::cout << std::endl;
}

int main()
{
	try
	{
		std::cout << "Enter the elements of the vector separated by a space: ";
		auto vector = GetVectorFromStream(std::cin);

		SubtractMedianFromElements(vector);
		std::sort(vector.begin(), vector.end());

		std::cout << "Sorted vector centered relative to 0: ";
		PrintVector(vector);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}