#ifndef EX2_CALCULATOR_H
#define EX2_CALCULATOR_H

#include <map>
#include <string>
#include "ValueProvider.h"
#include "Variable.h"
#include "Function.h"
#include "functional"

class Calculator
{
public:
	std::shared_ptr<Variable> InitVar(const std::string& name);

	void DeclareAndSetVariable(const std::string& name, double value);

	void DeclareAndSetVariable(const std::string& lname, const std::string& rname);

	void InitFn(const std::string& lname, const std::string& rname);

	void InitFn(
		const std::string& name,
		const std::string& leftOperandName,
		Operation operation,
		const std::string& rightOperandName
	);

	[[nodiscard]] double GetValue(const std::string& name) const;

	void GetVariables(const std::function<void(const std::map<std::string, std::shared_ptr<Variable>>&)>&) const;

	void GetFunctions(const std::function<void(const std::map<std::string, std::shared_ptr<Function>>&)>&) const;

private:
	std::map<std::string, std::shared_ptr<Variable>> m_variables;
	std::map<std::string, std::shared_ptr<Function>> m_functions;

	[[nodiscard]] std::shared_ptr<Variable> FindVariable(const std::string& name) const noexcept;

	[[nodiscard]] std::shared_ptr<Function> FindFunction(const std::string& name) const noexcept;

	[[nodiscard]] std::shared_ptr<ValueProvider> GetValueProvider(const std::string& name) const;

	[[nodiscard]] std::shared_ptr<ValueProvider> FindValueProvider(const std::string& name) const noexcept;

	void CheckValueProviderRedefinition(const std::string& name) const;

	void ValidateValueProviderName(const std::string& name) const;

	std::shared_ptr<Variable> FindOrCreateVariable(const std::string& name);
};


#endif //EX2_CALCULATOR_H
