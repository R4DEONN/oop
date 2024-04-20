#include <sstream>
#include <regex>
#include <iomanip>
#include "CustomExceptions.h"
#include "CalculatorController.h"

CalculatorController::CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator), m_input(input), m_output(output), m_actionMap({
	{ "var",       [this](std::istream& strm)
				   { Var(strm); }},
	{ "let",       [this](std::istream& strm)
				   { Let(strm); }},
	{ "fn",        [this](std::istream& strm)
				   { Fn(strm); }},
	{ "print",     [this](std::istream& strm)
				   { Print(strm); }},
	{ "printvars", [this](std::istream& strm)
				   { PrintVars(); }},
	{ "printfns",  [this](std::istream& strm)
				   { PrintFns(); }},
})
{
}

bool CalculatorController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	if (commandLine.empty())
	{
		return true;
	}
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void CalculatorController::Var(std::istream& args)
{
	try
	{
		std::string name;
		if (args >> name)
		{
			m_calculator.InitVar(name);
		}
		else
		{
			throw std::iostream::failure("Error in reading the input stream");
		}
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorController::Let(std::istream& args)
{
	try
	{
		std::string argsStr;
		std::getline(args, argsStr);

		std::istringstream iss(argsStr);
		std::string name, equalChar, value;

		if (!(iss >> name >> equalChar >> value)) {
			throw SyntaxException("Incorrect syntax of function declaration");
		}

		std::istringstream valuestream(value);
		double num;

		if (valuestream >> num)
		{
			m_calculator.DeclareAndSetVariable(name, num);
		}
		else
		{
			m_calculator.DeclareAndSetVariable(name, value);
		}
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorController::Fn(std::istream& args)
{
	try
	{
		std::string argsStr;
		std::getline(args, argsStr);

		std::istringstream iss(argsStr);
		std::string name, equalChar, leftOperand, operation, rightOperand;

		if ((iss >> name >> equalChar >> leftOperand) && !(iss >> operation)) {
			m_calculator.InitFn(name, leftOperand);
			return;
		}

		if (!(iss >> rightOperand)) {
			throw SyntaxException("Incorrect syntax of function declaration");
		}

		char c;
		if (iss.get(c)) {
			throw SyntaxException("Incorrect syntax of function declaration");
		}

		Operation op = GetOperation(operation);

		m_calculator.InitFn(name, leftOperand, op, rightOperand);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorController::Print(std::istream& args)
{
	try
	{
		std::string name;
		if (args >> name)
		{
			m_output << std::fixed << std::setprecision(2) << m_calculator.GetValue(name) << std::endl;
		}
		else
		{
			throw std::iostream::failure("Error in reading the input stream");
		}
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorController::PrintVars()
{
	m_calculator.GetVariables([this](const std::map<std::string, std::shared_ptr<Variable>>& vars) {
		for (const auto& var : vars)
		{
			m_output << var.first << ":" << var.second->GetValue() << std::endl;
		}
	});
}

void CalculatorController::PrintFns()
{
	m_calculator.GetFunctions([this](const std::map<std::string, std::shared_ptr<Function>>& funcs) {
		for (const auto& func : funcs)
		{
			m_output << func.first << ":" << func.second->GetValue() << std::endl;
		}
	});
}

Operation CalculatorController::GetOperation(const std::string& operationString)
{
	if (operationString == "+")
	{
		return Operation::Plus;
	}
	if (operationString == "-")
	{
		return Operation::Minus;
	}
	if (operationString == "*")
	{
		return Operation::Multiply;
	}
	if (operationString == "/")
	{
		return Operation::Division;
	}

	throw std::invalid_argument("Unknown operation '" + operationString + "'");
}