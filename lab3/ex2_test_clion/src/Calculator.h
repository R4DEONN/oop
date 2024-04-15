#ifndef EX2_CALCULATOR_H
#define EX2_CALCULATOR_H

#include <map>
#include <string>
#include "Variable.h"
#include "Function.h"

constexpr std::string Nan = "NaN";

class Calculator
{
public:
	std::shared_ptr<Variable> InitVar(const std::string& name);

	void AssignValueToVar(const std::string& name, double value);

	void AssignValueToVar(const std::string& lname, const std::string& rname);

	void InitFn(const std::string& lname, const std::string& rname);

	void InitFn(
		const std::string& name,
		const std::string& leftOperandName,
		Operation operation,
		const std::string& rightOperandName
	);

	std::string GetValue(const std::string& name);

	std::map<std::string, std::shared_ptr<Variable>> GetVariables();

	std::map<std::string, std::shared_ptr<Function>> GetFunctions();

private:
	std::map<std::string, std::shared_ptr<Variable>> m_variables;
	std::map<std::string, std::shared_ptr<Function>> m_functions;

	std::shared_ptr<Variable> FindVariable(const std::string& name);

	std::shared_ptr<Function> FindFunction(const std::string& name);

	std::shared_ptr<Variable> GetOperand(const std::string& name);

	std::shared_ptr<Variable> FindOperand(const std::string& name) noexcept;
};


#endif //EX2_CALCULATOR_H
