#include "Calculator.h"
#include <sstream>
#include "CustomExceptions.h"

std::shared_ptr<Variable> Calculator::InitVar(const std::string& name)
{
	if (name.empty())
	{
		throw InvalidNameException("Variable must have a name");
	}
	auto it = m_variables.find(name);
	if (it != m_variables.end())
	{
		throw RedefinitionException("Redefinition of '" + name + "'");
	}

	auto variable = std::make_shared<Variable>();
	m_variables.emplace(name, variable);

	return variable;
}

Variable Calculator::GetVariable(const std::string& name)
{
	auto variable = FindOperand(name);
	if (variable == nullptr)
	{
		throw UndeclaredException("Undeclared variable '" + name + "'");
	}
	return *variable;
}

void Calculator::DeclareAndSetVariable(const std::string& name, double value)
{
	//TODO: remove duplicate
	//TODO: throw overflow
	auto variable = FindVariable(name);
	if (variable == nullptr)
	{
		variable = InitVar(name);
	}

	variable->SetValue(value);
}

void Calculator::DeclareAndSetVariable(const std::string& lname, const std::string& rname)
{
	auto leftVar = FindVariable(lname);
	if (leftVar == nullptr)
	{
		leftVar = InitVar(lname);
	}

	auto rightVar = FindVariable(rname);
	if (rightVar == nullptr)
	{
		throw UndeclaredException("Undeclared variable '" + rname + "'");
	}

	leftVar->SetValue(rightVar->GetValue());
}

std::map<std::string, std::shared_ptr<Variable>> Calculator::GetVariables()
{
	return m_variables;
}

void Calculator::InitFn(const std::string& lname, const std::string& rname)
{
	if (lname.empty())
	{
		throw InvalidNameException("Function must have a name");
	}
	auto variable = FindOperand(lname);
	if (variable != nullptr)
	{
		throw RedefinitionException("Redefinition of '" + lname + "'");
	}

	auto operand = GetOperand(rname);
	auto function = std::make_shared<Function>(operand);
	operand->Subscribe(function);
	m_functions.emplace(lname, function);
}

void Calculator::InitFn(
	const std::string& name,
	const std::string& leftOperandName,
	Operation operation,
	const std::string& rightOperandName
)
{
	//TODO: remove duplicate
	if (name.empty())
	{
		throw InvalidNameException("Function must have a name");
	}
	auto variable = FindOperand(name);
	if (variable != nullptr)
	{
		throw RedefinitionException("Redefinition of '" + name + "'");
	}
	if (operation == Operation::None)
	{
		throw std::invalid_argument("Unknown operation");
	}

	auto leftOperand = GetOperand(leftOperandName);
	auto rightOperand = GetOperand(rightOperandName);
	auto function = std::make_shared<Function>(leftOperand, operation, rightOperand);
	leftOperand->Subscribe(function);
	rightOperand->Subscribe(function);
	m_functions.emplace(name, function);
}

std::shared_ptr<Variable> Calculator::FindVariable(const std::string& name)
{
	auto it = m_variables.find(name);
	if (it == m_variables.end())
	{
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Function> Calculator::FindFunction(const std::string& name)
{
	auto it = m_functions.find(name);
	if (it == m_functions.end())
	{
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Variable> Calculator::FindOperand(const std::string& name) noexcept
{
	auto operand = FindVariable(name);
	if (operand == nullptr)
	{
		operand = FindFunction(name);
		if (operand == nullptr)
		{
			return nullptr;
		}
	}
	return operand;
}


std::shared_ptr<Variable> Calculator::GetOperand(const std::string& name)
{
	auto operand = FindOperand(name);
	if (operand == nullptr)
	{
		throw UndeclaredException("Undeclared variable '" + name + "'");
	}
	return operand;
}

std::map<std::string, std::shared_ptr<Function>> Calculator::GetFunctions()
{
	return m_functions;
}
