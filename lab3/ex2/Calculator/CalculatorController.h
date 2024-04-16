#pragma once

#include "Calculator.h"
#include "iostream"
#include "functional"
#include "map"
#include "string"

class CalculatorController
{
public:
	CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};