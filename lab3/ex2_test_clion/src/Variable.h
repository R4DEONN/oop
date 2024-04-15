#ifndef EX2_VARIABLE_H
#define EX2_VARIABLE_H

#include <string>
#include <set>
#include "ISubscriber.h"
#include <memory>

class Variable
{
public:
	Variable() = default;
	explicit Variable(double value);
	[[nodiscard]] double GetValue() const;
	[[nodiscard]] bool IsUndefined() const;
	virtual void SetValue(double value);

	void Subscribe(const std::shared_ptr<ISubscriber>& sub);
	void Unsubscribe(const std::shared_ptr<ISubscriber>& sub);
	void NotifySubscribers();

protected:
	double m_value = 0;
	bool m_isUndefined = true;
	std::set<std::shared_ptr<ISubscriber>> m_subscribers;

};


#endif //EX2_VARIABLE_H
