#pragma once
#include <functional>
#include <iostream>
#include <map>

class Car;

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);
	bool Info(std::istream& args);

private:
	std::string GetStringDirection();

	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};