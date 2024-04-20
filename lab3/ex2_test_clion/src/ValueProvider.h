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

	void Subscribe(ISubscriber* sub);

	virtual ~ValueProvider() = default;

protected:
	void NotifySubscribers() const;
	double m_value = std::numeric_limits<double>::quiet_NaN();

private:
	std::set<ISubscriber*> m_subscribers;
};


#endif //EX2_VALUEPROVIDER_H
