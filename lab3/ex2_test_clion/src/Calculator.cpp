#include "Calculator.h"
#include "CustomExceptions.h"

std::shared_ptr<Variable> Calculator::InitVar(const std::string& name)
{
	ValidateVariableName(name);

	auto variable = std::make_shared<Variable>();
	m_variables.emplace(name, variable);

	return variable;
}

Variable Calculator::GetVariable(const std::string& name)
{
	return *GetOperand(name);
}

void Calculator::DeclareAndSetVariable(const std::string& name, double value)
{
	auto variable = FindOrCreateVariable(name);
	variable->SetValue(value);
}

void Calculator::DeclareAndSetVariable(const std::string& lname, const std::string& rname)
{
	auto leftVar = FindOrCreateVariable(lname);

	auto rightVar = GetOperand(rname);

	leftVar->SetValue(rightVar->GetValue());
}

std::map<std::string, std::shared_ptr<Variable>> Calculator::GetVariables()
{
	return m_variables;
}

void Calculator::InitFn(const std::string& lname, const std::string& rname)
{
	ValidateVariableName(lname);

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
	ValidateVariableName(name);

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

std::shared_ptr<Variable> Calculator::FindVariable(const std::string& name) noexcept
{
	auto it = m_variables.find(name);
	if (it == m_variables.end())
	{
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Function> Calculator::FindFunction(const std::string& name) noexcept
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

void Calculator::CheckOperandRedefinition(const std::string& name)
{
	auto it = FindOperand(name);
	if (it != nullptr)
	{
		throw RedefinitionException("Redefinition of '" + name + "'");
	}
}

void Calculator::ValidateVariableName(const std::string& name)
{
	if (name.empty())
	{
		throw InvalidNameException("Variable must have a name");
	}
	CheckOperandRedefinition(name);
}

std::shared_ptr<Variable> Calculator::FindOrCreateVariable(const std::string& name)
{
	auto variable = FindVariable(name);
	if (variable == nullptr)
	{
		variable = InitVar(name);
	}
	return variable;
}