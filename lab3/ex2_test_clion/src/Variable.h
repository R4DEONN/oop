#ifndef EX2_VARIABLE_H
#define EX2_VARIABLE_H

#include <string>
#include <set>
#include "ISubscriber.h"
#include <memory>
#include <cmath>
#include "ValueProvider.h"

class Variable : public ValueProvider
{
public:
	Variable() = default;
	explicit Variable(double value);
	void SetValue(double value);
};


#endif //EX2_VARIABLE_H
