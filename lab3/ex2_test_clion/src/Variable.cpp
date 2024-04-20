#include "Variable.h"

Variable::Variable(double value)
	: ValueProvider(value)
{
}

void Variable::SetValue(double value)
{
	m_value = value;
	NotifySubscribers();
}