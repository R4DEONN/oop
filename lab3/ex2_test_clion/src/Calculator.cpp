#include "Calculator.h"
#include "CustomExceptions.h"

std::shared_ptr<Variable> Calculator::InitVar(const std::string& name)
{
	ValidateValueProviderName(name);

	auto variable = std::make_shared<Variable>();
	m_variables.emplace(name, variable);

	return variable;
}

double Calculator::GetValue(const std::string& name) const
{
	return GetValueProvider(name)->GetValue();
}

void Calculator::DeclareAndSetVariable(const std::string& name, double value)
{
	auto variable = FindOrCreateVariable(name);
	variable->SetValue(value);
}

void Calculator::DeclareAndSetVariable(const std::string& lname, const std::string& rname)
{
	auto leftVar = FindOrCreateVariable(lname);

	auto rightVar = GetValueProvider(rname);

	leftVar->SetValue(rightVar->GetValue());
}

void Calculator::GetVariables(const std::function<void(const std::map<std::string, std::shared_ptr<Variable>>&)>& cb) const
{
	cb(m_variables);
}

void Calculator::InitFn(const std::string& lname, const std::string& rname)
{
	ValidateValueProviderName(lname);

	auto operand = GetValueProvider(rname);
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
	ValidateValueProviderName(name);

	if (operation == Operation::None)
	{
		throw std::invalid_argument("Unknown operation");
	}

	auto leftOperand = GetValueProvider(leftOperandName);
	auto rightOperand = GetValueProvider(rightOperandName);
	auto function = std::make_shared<Function>(leftOperand, operation, rightOperand);
	leftOperand->Subscribe(function);
	rightOperand->Subscribe(function);
	m_functions.emplace(name, function);
}

std::shared_ptr<Variable> Calculator::FindVariable(const std::string& name) const noexcept
{
	auto it = m_variables.find(name);
	if (it == m_variables.end())
	{
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Function> Calculator::FindFunction(const std::string& name) const noexcept
{
	auto it = m_functions.find(name);
	if (it == m_functions.end())
	{
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<ValueProvider> Calculator::FindValueProvider(const std::string& name) const noexcept
{
	std::shared_ptr<ValueProvider> operand = FindVariable(name);
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


std::shared_ptr<ValueProvider> Calculator::GetValueProvider(const std::string& name) const
{
	std::shared_ptr<ValueProvider> operand = FindValueProvider(name);
	if (operand == nullptr)
	{
		throw UndeclaredException("Undeclared variable '" + name + "'");
	}
	return operand;
}

void Calculator::GetFunctions(const std::function<void(const std::map<std::string, std::shared_ptr<Function>>&)>& cb) const
{
	cb(m_functions);
}

void Calculator::CheckValueProviderRedefinition(const std::string& name) const
{
	auto it = FindValueProvider(name);
	if (it != nullptr)
	{
		throw RedefinitionException("Redefinition of '" + name + "'");
	}
}

void Calculator::ValidateValueProviderName(const std::string& name) const
{
	if (name.empty())
	{
		throw InvalidNameException("Variable must have a name");
	}
	CheckValueProviderRedefinition(name);
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