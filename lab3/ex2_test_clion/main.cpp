#include <iostream>
#include <fstream>
#include "src/Calculator.h"
#include "src/CalculatorController.h"

int main()
{
//	std::ifstream in("1.txt");

	Calculator calculator;
	CalculatorController calculatorController(calculator, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!calculatorController.HandleCommand())
		{
			std::cout << "Unknown command" << std::endl;
		}
	}

	return EXIT_SUCCESS;
}