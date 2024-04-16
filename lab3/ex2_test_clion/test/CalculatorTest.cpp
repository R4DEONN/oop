#include "catch2/catch_test_macros.hpp"
#include "calculator.h"

TEST_CASE("VarX") {
	Calculator calculator;
	calculator.InitVar("x");
	auto vars = calculator.GetVariables();
	REQUIRE(vars["x"]->IsUndefined());
	REQUIRE(vars["x"]->GetValue() == 0);
}