#include <stdexcept>
#include "Function.h"

Function::Function(const std::shared_ptr<Variable>& variable)
	: Variable(variable->GetValue()),
	  m_leftOperand(variable),
	  m_operation(Operation::None),
	  m_rightOperand(nullptr)
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
	auto result = GetOperationResult();
	SetValue(result);
}

double Function::GetOperationResult()
{
	switch (m_operation)
	{
	case Operation::Plus:
		return m_leftOperand->GetValue() + m_rightOperand->GetValue();
	case Operation::Minus:
		return m_leftOperand->GetValue() - m_rightOperand->GetValue();
	case Operation::Multiply:
		return m_leftOperand->GetValue() * m_rightOperand->GetValue();
	case Operation::Division:
		return m_leftOperand->GetValue() / m_rightOperand->GetValue();
	case Operation::None:
		return m_leftOperand->GetValue();
	default:
		throw std::invalid_argument("Unknown operation");
	}
}

void Function::Update()
{
	SetValue(GetOperationResult());
	NotifySubscribers();
}
