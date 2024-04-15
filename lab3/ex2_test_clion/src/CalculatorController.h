#ifndef EX2_CALCULATORCONTROLLER_H
#define EX2_CALCULATORCONTROLLER_H

#include <iostream>
#include <functional>
#include <map>
#include "Calculator.h"

class CalculatorController
{
public:
	CalculatorController(Calculator& args, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	void Var(std::istream& args);
	void Let(std::istream& args);
	void Fn(std::istream& args);
	void Print(std::istream& args);
	void PrintVars(std::istream& args);
	void PrintFns(std::istream& args);

	Operation GetOperation(const std::string& operationString);

	using Handler = std::function<void(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};


#endif //EX2_CALCULATORCONTROLLER_H