#include <stdexcept>
#include "Function.h"

Function::Function(const std::shared_ptr<Variable>& valueProvider)
	: Variable(valueProvider->GetValue()),
	  m_leftOperand(valueProvider),
	  m_operation(Operation::None),
	  m_rightOperand(valueProvider)
{
}

Function::Function(
	const std::shared_ptr<Variable>& leftOperand,
	Operation operation,
	const std::shared_ptr<Variable>& rightOperand
	)
	: Variable(),
	  m_leftOperand(leftOperand),
	  m_operation(operation),
	  m_rightOperand(rightOperand)
{
	auto result = GetOperationResult(leftOperand, operation, rightOperand);
	if (result)
	{
		m_isUndefined = false;
		m_value = result.value();
	}
}

std::optional<double> Function::GetOperationResult(
	const std::shared_ptr<Variable>& leftOperand,
	Operation operation,
	const std::shared_ptr<Variable>& rightOperand
	)
{
	if (leftOperand->IsUndefined() || rightOperand->IsUndefined())
	{
		return std::nullopt;
	}

	switch (operation)
	{
	case Operation::Plus:
		return leftOperand->GetValue() + rightOperand->GetValue();
	case Operation::Minus:
		return leftOperand->GetValue() - rightOperand->GetValue();
	case Operation::Multiply:
		return leftOperand->GetValue() * rightOperand->GetValue();
	case Operation::Division:
		return leftOperand->GetValue() / rightOperand->GetValue();
	case Operation::None:
		return leftOperand->GetValue();
	default:
		throw std::invalid_argument("Unknown operation");
	}
}

void Function::Update()
{
	auto result = GetOperationResult(m_leftOperand, m_operation, m_rightOperand);
	if (result)
	{
		m_isUndefined = false;
		m_value = result.value();
	}
	else
	{
		m_isUndefined = true;
	}
	NotifySubscribers();
}
