#include <iostream>
#include "Car.h"
#include "CarController.h"

using namespace std::string_literals;

int main()
{
	Car car;
	CarController carController(car, std::cin, std::cout);

	std::string command;

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!carController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
}