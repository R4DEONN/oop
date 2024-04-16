#ifndef EX2_VARIABLE_H
#define EX2_VARIABLE_H

#include <string>
#include <set>
#include "ISubscriber.h"
#include <memory>
#include <cmath>

class Variable
{
public:
	Variable() = default;
	explicit Variable(double value);
	[[nodiscard]] double GetValue() const;
	virtual void SetValue(double value);

	void Subscribe(const std::shared_ptr<ISubscriber>& sub);
	void NotifySubscribers();

protected:
	double m_value = std::nan("");
	std::set<std::shared_ptr<ISubscriber>> m_subscribers;

};


#endif //EX2_VARIABLE_H
