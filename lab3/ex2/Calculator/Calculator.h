#pragma once
#include <map>
#include <string>
#include <functional>

class Calculator
{
public:

private:
	std::map<std::string, double> variables;
	std::map<std::string, std::function<bool(std::istream& args)>> variables;
};