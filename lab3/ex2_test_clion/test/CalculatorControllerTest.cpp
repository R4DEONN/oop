#include "catch2/catch_test_macros.hpp"
#include "CalculatorController.h"
#include <sstream>

void HandleCommands(CalculatorController& calculatorController, std::istream& input)
{
	while (!input.eof() && !input.fail())
	{
		calculatorController.HandleCommand();
	}
}

TEST_CASE("Var", "[CalculatorController]")
{
	Calculator calculator;

	std::ostringstream output;
	std::istringstream input(
		"var x\n"
		"print x\n"
		"var y\n"
		"printvars\n"
	);

	CalculatorController calculatorController(calculator, input, output);
	HandleCommands(calculatorController, input);

	std::string expectedOutput =
		"nan\n"
		"x:nan\n"
		"y:nan\n";

	REQUIRE(expectedOutput == output.str());
}

TEST_CASE("Let", "[CalculatorController]")
{
	Calculator calculator;
	std::ostringstream output;
	std::istringstream input(
		"var x\n"
		"let x = 10\n"
		"print x\n"
		"let y = 2.53421\n"
		"printvars\n"
	);

	CalculatorController calculatorController(calculator, input, output);
	HandleCommands(calculatorController, input);

	std::string expectedOutput =
		"10.00\n"
		"x:10.00\n"
		"y:2.53\n";

	REQUIRE(expectedOutput == output.str());
}

TEST_CASE("Fn", "[CalculatorController]")
{
	Calculator calculator;
	std::ostringstream output;
	std::istringstream input(
		"var x\n"
		"fn z = x\n"
		"print z\n"
		"let x = 10\n"
		"print z\n"
		"let y = 2.53421\n"
		"fn w = x + y\n"
		"print w\n"
		"fn k = z + w\n"
		"print k\n"
		"let x = 2\n"
		"printfns\n"
	);

	CalculatorController calculatorController(calculator, input, output);
	HandleCommands(calculatorController, input);

	std::string expectedOutput =
		"nan\n"
		"10.00\n"
		"12.53\n"
		"22.53\n"
		"k:6.53\n"
		"w:4.53\n"
		"z:2.00\n";

	REQUIRE(expectedOutput == output.str());
}