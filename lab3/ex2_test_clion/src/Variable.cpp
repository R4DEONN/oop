#include "Variable.h"

Variable::Variable(double value)
	: m_value(value),
	  m_isUndefined(false)
{
}

double Variable::GetValue() const
{
	return m_value;
}

bool Variable::IsUndefined() const
{
	return m_isUndefined;
}

void Variable::SetValue(double value)
{
	m_isUndefined = false;
	m_value = value;
	NotifySubscribers();
}

void Variable::Subscribe(const std::shared_ptr<ISubscriber>& sub)
{
	m_subscribers.insert(sub);
}

void Variable::Unsubscribe(const std::shared_ptr<ISubscriber>& sub)
{
	m_subscribers.erase(sub);
}

void Variable::NotifySubscribers()
{
	for (auto sub : m_subscribers)
	{
		sub->Update();
	}
}
