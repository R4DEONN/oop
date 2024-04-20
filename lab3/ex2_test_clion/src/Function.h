#ifndef EX2_FUNCTION_H
#define EX2_FUNCTION_H

#include "ValueProvider.h"
#include "ISubscriber.h"

enum class Operation
{
	None,
	Plus,
	Minus,
	Multiply,
	Division,
};

class Function : public ValueProvider, public ISubscriber
{
public:
	explicit Function(const std::shared_ptr<ValueProvider>& variable);

	Function(
		const std::shared_ptr<ValueProvider>& leftOperand,
		Operation operation,
		const std::shared_ptr<ValueProvider>& rightOperand
	);

	void Update() override;

private:
	std::shared_ptr<ValueProvider> m_leftOperand;
	Operation m_operation;
	std::shared_ptr<ValueProvider> m_rightOperand;

	double GetOperationResult();
};

#endif //EX2_FUNCTION_H