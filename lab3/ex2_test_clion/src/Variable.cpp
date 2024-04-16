#include "Variable.h"

Variable::Variable(double value)
	: m_value(value)
{
}

double Variable::GetValue() const
{
	return m_value;
}

void Variable::SetValue(double value)
{
	m_value = value;
	NotifySubscribers();
}

void Variable::Subscribe(const std::shared_ptr<ISubscriber>& sub)
{
	m_subscribers.insert(sub);
}

void Variable::NotifySubscribers()
{
	for (const auto& sub : m_subscribers)
	{
		sub->Update();
	}
}
