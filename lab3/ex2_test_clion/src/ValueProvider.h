#ifndef EX2_VALUEPROVIDER_H
#define EX2_VALUEPROVIDER_H

#include <string>
#include <set>
#include "ISubscriber.h"
#include <memory>
#include <cmath>

class ValueProvider
{
public:
	ValueProvider() = default;

	explicit ValueProvider(double value);

	[[nodiscard]] double GetValue() const;

	void Subscribe(const std::shared_ptr<ISubscriber>& sub);

	virtual ~ValueProvider() = default;

protected:
	void NotifySubscribers() const;
	double m_value = std::nan("");

private:
	std::set<std::shared_ptr<ISubscriber>> m_subscribers;
};


#endif //EX2_VALUEPROVIDER_H
