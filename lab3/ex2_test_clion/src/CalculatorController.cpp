#include <sstream>
#include <regex>
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
		//TODO: throw
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
		std::istreambuf_iterator<char> eos;
		std::string argsStr(std::istreambuf_iterator<char>(args), eos);
		std::regex pattern(R"(\s*(\w+)\s*=\s*(\d+.?\d+|\w+))");
		std::smatch matches;

		if (!std::regex_match(argsStr, matches, pattern))
		{
			throw SyntaxException("incorrect letting variable");
		}

		std::istringstream valuestream(matches[2]);
		double num;

		if (valuestream >> num)
		{
			m_calculator.DeclareAndSetVariable(matches[1], num);
		}
		else
		{
			m_calculator.DeclareAndSetVariable(matches[1], matches[2]);
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

		std::regex pattern(R"(\s*(\w+)\s*=\s*(\w+)(?:\s*([+*\/-])\s*(\w+))?)");
		std::smatch matches;

		if (!std::regex_match(argsStr, matches, pattern))
		{
			throw SyntaxException("Incorrect syntax of function declaration");
		}

		if (matches.size() == 3)
		{
			m_calculator.InitFn(matches[1], matches[2]);
		}
		else if (matches.size() == 5)
		{
			m_calculator.InitFn(
				matches[1],
				matches[2],
				GetOperation(matches[3]),
				matches[4]
			);
		}
		else
		{
			throw SyntaxException("Incorrect syntax of function declaration");
		}
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
			auto var = m_calculator.GetVariable(name);
			m_output << var.GetValue() << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorController::PrintVars()
{
	//TODO: remove dublicate
	auto variables = m_calculator.GetVariables();
	for (auto& pair: variables)
	{
		m_output << pair.first << ":" << pair.second->GetValue() << std::endl;
	}
}

void CalculatorController::PrintFns()
{
	auto functions = m_calculator.GetFunctions();
	for (auto& pair: functions)
	{
		m_output << pair.first << ":" << pair.second->GetValue() << std::endl;
	}
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