#include <stdexcept>
#include "Function.h"

Function::Function(const std::shared_ptr<ValueProvider>& valueProvider)
	: ValueProvider(valueProvider->GetValue()),
	  m_leftOperand(valueProvider),
	  m_operation(Operation::None),
	  m_rightOperand(nullptr)
{
	std::cout << "Function is created" << std::endl;
	valueProvider->Subscribe(this);
}

Function::Function(
	const std::shared_ptr<ValueProvider>& leftOperand,
	Operation operation,
	const std::shared_ptr<ValueProvider>& rightOperand
)
	: ValueProvider(),
	  m_leftOperand(leftOperand),
	  m_operation(operation),
	  m_rightOperand(rightOperand)
{
	m_leftOperand->Subscribe(this);
	m_rightOperand->Subscribe(this);
	auto result = GetOperationResult();
	m_value = result;
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
	m_value = GetOperationResult();
	NotifySubscribers();
}
