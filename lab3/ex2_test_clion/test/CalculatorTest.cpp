#include "catch2/catch_test_macros.hpp"
#include "calculator.h"
#include "CustomExceptions.h"

auto value = 20.3524;
std::string varXName = "x";
std::string varYName = "y";
std::string varZName = "z";

TEST_CASE("Var variables", "[calculator]")
{
	Calculator calculator;

	SECTION("Var x should be undefined")
	{
		calculator.InitVar(varXName);
		auto var = calculator.GetVariable(varXName);
		REQUIRE(std::isnan(var.GetValue()));
	}

	SECTION("Var without name should throw exception")
	{
		REQUIRE_THROWS_AS(calculator.InitVar(""), InvalidNameException);
	}

	SECTION("Redefinition variable should throw exception")
	{
		calculator.InitVar(varXName);
		REQUIRE_THROWS_AS(calculator.InitVar(varXName), RedefinitionException);
	}
}

TEST_CASE("Letting variable", "[calculator]")
{
	Calculator calculator;
	calculator.DeclareAndSetVariable(varYName, value);
	auto varY = calculator.GetVariable(varYName);
	REQUIRE(!std::isnan(varY.GetValue()));
	REQUIRE(varY.GetValue() == value);

	SECTION("Letting an undeclared variable with double")
	{
		calculator.DeclareAndSetVariable(varXName, value);
		auto var = calculator.GetVariable(varXName);
		REQUIRE(!std::isnan(var.GetValue()));
		REQUIRE(var.GetValue() == value);
	}

	SECTION("Letting a declared variable with double")
	{
		calculator.InitVar(varXName);
		calculator.DeclareAndSetVariable(varXName, value);
		auto var = calculator.GetVariable(varXName);
		REQUIRE(!std::isnan(var.GetValue()));
		REQUIRE(var.GetValue() == value);
	}

	SECTION("Letting an undeclared variable with another variable")
	{
		calculator.DeclareAndSetVariable(varXName, varYName);
		auto var = calculator.GetVariable(varXName);
		REQUIRE(!std::isnan(var.GetValue()));
		REQUIRE(var.GetValue() == value);
	}

	SECTION("Letting an undeclared variable with undeclared variable should throw exception")
	{
		REQUIRE_THROWS_AS(calculator.DeclareAndSetVariable(varXName, varZName), UndeclaredException);
	}

	SECTION("Letting a declared variable with another variable")
	{
		calculator.InitVar(varXName);
		calculator.DeclareAndSetVariable(varXName, varYName);
		auto var = calculator.GetVariable(varXName);
		REQUIRE(!std::isnan(var.GetValue()));
		REQUIRE(var.GetValue() == value);
	}

	SECTION("Letting a declared variable with undeclared variable should throw exception")
	{
		calculator.InitVar(varXName);
		REQUIRE_THROWS_AS(calculator.DeclareAndSetVariable(varXName, varZName), UndeclaredException);
	}
}

TEST_CASE("Getting value of variable or function", "[calculator]")
{
	Calculator calculator;

	SECTION("Accessing an undeclared variable")
	{
		REQUIRE_THROWS_AS(calculator.GetVariable(varZName), UndeclaredException);
	}

	SECTION("Accessing an undefined variable")
	{
		calculator.InitVar(varXName);
		REQUIRE(std::isnan(calculator.GetVariable(varXName).GetValue()));
	}

	SECTION("Accessing a defined variable")
	{
		calculator.DeclareAndSetVariable(varYName, 20);
		REQUIRE(calculator.GetVariable(varYName).GetValue() == 20);
	}
}

TEST_CASE("Declare function with one variable", "[calculator]")
{
	Calculator calculator;

	SECTION("Redefinition should throw exception")
	{
		REQUIRE_THROWS_AS(calculator.InitFn(varXName, varZName), UndeclaredException);
	}

	SECTION("Empty name")
	{
		REQUIRE_THROWS_AS(calculator.InitFn("", varZName), InvalidNameException);
	}

	SECTION("Declare with double variable then change value of variable")
	{
		calculator.DeclareAndSetVariable(varXName, value);
		calculator.InitFn(varYName, varXName);
		auto func = calculator.GetVariable(varYName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value);

		auto newValue = value + 1;
		calculator.DeclareAndSetVariable(varXName, newValue);
		func = calculator.GetVariable(varYName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == newValue);
	}

	SECTION("Declare with function then change value of function")
	{
		calculator.DeclareAndSetVariable(varXName, value);
		calculator.InitFn(varYName, varXName);
		calculator.InitFn(varZName, varYName);
		auto func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value);

		auto newValue = value + 1;
		calculator.DeclareAndSetVariable(varXName, newValue);
		func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == newValue);
	}
}

TEST_CASE("Declare function with operation", "[calculator]")
{
	Calculator calculator;
	calculator.DeclareAndSetVariable(varXName, value);
	calculator.DeclareAndSetVariable(varYName, value);

	SECTION("Empty name")
	{
		REQUIRE_THROWS_AS(
			calculator.InitFn(
				"",
				varXName,
				Operation::Plus,
				varYName
			),
			InvalidNameException
		);
	}

	SECTION("Redefinition should throw exception")
	{
		REQUIRE_THROWS_AS(
			calculator.InitFn(
				varXName,
				varXName,
				Operation::Plus,
				varYName
			),
			RedefinitionException
		);
	}

	SECTION("fn z = x + y then change x")
	{
		calculator.InitFn(
			varZName,
			varXName,
			Operation::Plus,
			varYName
		);

		auto func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value + value);

		calculator.DeclareAndSetVariable(varXName, value + value);
		func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value + value + value);
	}

	SECTION("fn z = x - y then change x and y")
	{
		calculator.InitFn(
			varZName,
			varXName,
			Operation::Minus,
			varYName
		);

		auto func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value - value);

		calculator.DeclareAndSetVariable(varXName, 0);
		calculator.DeclareAndSetVariable(varYName, 0);
		func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == 0);
	}

	SECTION("fn z = x * y then change x")
	{
		calculator.InitFn(
			varZName,
			varXName,
			Operation::Multiply,
			varYName
		);

		auto func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value * value);

		calculator.DeclareAndSetVariable(varXName, value * value);
		func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value * value * value);
	}

	SECTION("fn z = x / y then change x")
	{
		calculator.InitFn(
			varZName,
			varXName,
			Operation::Division,
			varYName
		);

		auto func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value / value);

		calculator.DeclareAndSetVariable(varXName, value / value);
		func = calculator.GetVariable(varZName);
		REQUIRE(!std::isnan(func.GetValue()));
		REQUIRE(func.GetValue() == value / value / value);
	}

	SECTION("Operation::None in function should throw exception")
	{
		REQUIRE_THROWS_AS(
			calculator.InitFn(
				varZName,
				varXName,
				Operation::None,
				varYName
			),
			std::invalid_argument
		);
	}
}
