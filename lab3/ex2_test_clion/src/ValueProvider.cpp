#include "ValueProvider.h"

ValueProvider::ValueProvider(double value)
	: m_value(value)
{
}

double ValueProvider::GetValue() const
{
	return m_value;
}

void ValueProvider::Subscribe(ISubscriber* sub)
{
	m_subscribers.insert(sub);
}

void ValueProvider::NotifySubscribers() const
{
	for (const auto& sub : m_subscribers)
	{
		sub->Update();
	}
}
