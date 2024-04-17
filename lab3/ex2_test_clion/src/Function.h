#ifndef EX2_FUNCTION_H
#define EX2_FUNCTION_H

#include <optional>
#include "Variable.h"
#include "ISubscriber.h"

enum class Operation
{
	None,
	Plus,
	Minus,
	Multiply,
	Division,
};

class Function : public Variable, public ISubscriber
{
public:
	explicit Function(const std::shared_ptr<Variable>& variable);

	Function(
		const std::shared_ptr<Variable>& leftOperand,
		Operation operation,
		const std::shared_ptr<Variable>& rightOperand
	);

	std::optional<double> static GetOperationResult(
		const std::shared_ptr<Variable>& leftOperand,
		Operation operation,
		const std::shared_ptr<Variable>& rightOperand
	);

	void Update() override;

private:
	std::shared_ptr<Variable> m_leftOperand;
	Operation m_operation;
	std::shared_ptr<Variable> m_rightOperand;
};

#endif //EX2_FUNCTION_H