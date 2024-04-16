#include "catch2/catch_test_macros.hpp"
#include "calculator.h"
#include "CustomExceptions.h"

TEST_CASE("Var variables", "[calculator]") {
	Calculator calculator;

	SECTION("Var x should be undefined") {
		calculator.InitVar("x");
		auto vars = calculator.GetVariables();
		REQUIRE(vars["x"]->IsUndefined());
	}

	SECTION("Var without name should throw exception") {
		REQUIRE_THROWS_AS(calculator.InitVar(""), InvalidNameException);
	}

	SECTION("Redefinition variable should throw exception") {
		std::string variableName = "x";
		calculator.InitVar(variableName);
		REQUIRE_THROWS_AS(calculator.InitVar(variableName), RedefinitionException);
	}
}

TEST_CASE("Letting variable", "[calculator]") {
	Calculator calculator;
	auto value = 20.3524;
	std::string varXName = "x";
	std::string varYName = "y";
	std::string varZName = "z";
	calculator.DeclareAndSetVariable(varYName, value);
	auto varY = calculator.GetVariables()[varYName];
	REQUIRE(!varY->IsUndefined());
	REQUIRE(varY->GetValue() == value);

	SECTION("Letting an undeclared variable with double") {
		calculator.DeclareAndSetVariable(varXName, value);
		auto var = calculator.GetVariables()[varXName];
		REQUIRE(!var->IsUndefined());
		REQUIRE(var->GetValue() == value);
	}

	SECTION("Letting a declared variable with double") {
		calculator.InitVar(varXName);
		calculator.DeclareAndSetVariable(varXName, value);
		auto var = calculator.GetVariables()[varXName];
		REQUIRE(!var->IsUndefined());
		REQUIRE(var->GetValue() == value);
	}

	SECTION("Letting an undeclared variable with another variable") {
		calculator.DeclareAndSetVariable(varXName, varYName);
		auto var = calculator.GetVariables()[varXName];
		REQUIRE(!var->IsUndefined());
		REQUIRE(var->GetValue() == value);
	}

	SECTION("Letting an undeclared variable with undeclared variable should throw exception") {
		REQUIRE_THROWS_AS(calculator.DeclareAndSetVariable(varXName, varZName), UndeclaredException);
	}

	SECTION("Letting a declared variable with another variable") {
		calculator.InitVar(varXName);
		calculator.DeclareAndSetVariable(varXName, varYName);
		auto var = calculator.GetVariables()[varXName];
		REQUIRE(!var->IsUndefined());
		REQUIRE(var->GetValue() == value);
	}

	SECTION("Letting a declared variable with undeclared variable should throw exception") {
		calculator.InitVar(varXName);
		REQUIRE_THROWS_AS(calculator.DeclareAndSetVariable(varXName, varZName), UndeclaredException);
	}
}

TEST_CASE("Getting value of variable or function", "[calculator]") {
	Calculator calculator;

	SECTION("Accessing an undeclared variable") {
		REQUIRE_THROWS_AS(calculator.GetValue("z"), UndeclaredException);
	}

	SECTION("Accessing an undefined variable") {
		calculator.InitVar("x");
		REQUIRE(calculator.GetValue("x") == Nan);
	}

	SECTION("Accessing a defined variable") {
		calculator.DeclareAndSetVariable("y", 20);
		REQUIRE(calculator.GetValue("y") == "20");
	}
}