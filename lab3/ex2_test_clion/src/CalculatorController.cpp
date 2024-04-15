#include <sstream>
#include <regex>
#include "CalculatorController.h"

CalculatorController::CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator), m_input(input), m_output(output), m_actionMap({
	{ "var",       [this](std::istream & strm) { Var(strm); } },
	{ "let",       [this](std::istream & strm) { Let(strm); } },
	{ "fn",        [this](std::istream & strm) { Fn(strm); } },
	{ "print",     [this](std::istream & strm) { Print(strm); } },
	{ "printvars", [this](std::istream & strm) { PrintVars(strm); } },
	{ "printfns",  [this](std::istream & strm) { PrintFns(strm); } },
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
		args >> name;
		m_calculator.InitVar(name);
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
		std::string equalCh;
		std::string name;
		std::string value;
		args >> name >> equalCh >> value;
		if (name.empty())
		{
			throw std::invalid_argument("Syntax Error: variable for assignment is not specified");
		}
		if (equalCh != "=")
		{
			throw std::invalid_argument("Syntax Error: letting variable without assignment sign");
		}
		if (value.empty())
		{
			throw std::invalid_argument("Syntax Error: new value of the variable is not specified");
		}

		std::istringstream valuestream(value);
		double num;

		if (valuestream >> num)
		{
			m_calculator.AssignValueToVar(name, num);
		}
		else
		{
			m_calculator.AssignValueToVar(name, value);
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
		std::istreambuf_iterator<char> eos;
		std::string argsStr(std::istreambuf_iterator<char>(args), eos);
		std::regex pattern("\\s*(\\w+)\\s*=\\s*(\\w+)");
		std::smatch matches;

		if (std::regex_match(argsStr, matches, pattern))
		{
			m_calculator.InitFn(matches[1], matches[2]);
		}
		else
		{
			std::regex pattern2("\\s*(\\w+)\\s*=\\s*(\\w+)\\s*([+*\\/-])\\s*(\\w+)");

			if (std::regex_match(argsStr, matches, pattern2))
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
				//TODO: throw
				std::cout << "No match found." << std::endl;
			}
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
		args >> name;
		m_output << m_calculator.GetValue(name) << std::endl;
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorController::PrintVars(std::istream& args)
{
	//TODO: remove dublicate
	auto variables = m_calculator.GetVariables();
	for (auto& pair: variables)
	{
		m_output << pair.first << ":";
		if (pair.second->IsUndefined())
		{
			m_output << Nan;
		}
		else
		{
			m_output << pair.second->GetValue();
		}
		m_output << std::endl;
	}
}

void CalculatorController::PrintFns(std::istream& args)
{
	auto functions = m_calculator.GetFunctions();
	for (auto& pair: functions)
	{
		m_output << pair.first << ":";
		if (pair.second->IsUndefined())
		{
			m_output << Nan;
		}
		else
		{
			m_output << pair.second->GetValue();
		}
		m_output << std::endl;
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
