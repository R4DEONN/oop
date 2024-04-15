#include "CarController.h"
#include "Car.h"
#include <iostream>
#include <string>
#include <sstream>

CarController::CarController(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "EngineOn", [this](std::istream& strm) {
			   return EngineOn(strm);
		   } },
		  { "EngineOff", bind(&CarController::EngineOn, this, std::placeholders::_1) },
		  { "SetGear", bind(&CarController::SetGear, this, std::placeholders::_1) },
		  { "SetSpeed", bind(&CarController::SetSpeed, this, std::placeholders::_1) },
		  { "Info", bind(&CarController::Info, this, std::placeholders::_1) },
	  })
{
}

bool CarController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CarController::EngineOn(std::istream& /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Car engine is turned on" << std::endl;
	return true;
}

bool CarController::EngineOff(std::istream& /*args*/)
{
	m_car.TurnOffEngine();
	m_output << "Car engine is turned off" << std::endl;
	return true;
}

bool CarController::SetGear(std::istream& args)
{
	int gear;
	args >> gear;
	if (m_car.SetGear(gear))
	{
		m_output << "Car gear is changed to " << gear << std::endl;
	}

	m_output << "Car gear is not changed" << std::endl;
	return true;
}

bool CarController::SetSpeed(std::istream& args)
{
	int speed;
	args >> speed;
	if (m_car.SetSpeed(speed))
	{
		m_output << "Car speed is changed to " << speed << std::endl;
	}

	m_output << "Car speed is not changed" << std::endl;
	return true;
}

bool CarController::Info(std::istream& /*args*/)
{
	m_output << "Car info:" << std::endl
			 << "  Gear: " << static_cast<int>(m_car.GetGear()) << std::endl
			 << "  Speed: " << m_car.GetSpeed() << std::endl
			 << "  Engine status: turned " << (m_car.IsTurnedOn() ? "on" : "off") << std::endl
			 << "  Move direction: " << GetStringDirection() << std::endl;

	return true;
}

std::string CarController::GetStringDirection()
{
	const auto direction = m_car.GetDirection();

	switch (direction)
	{
	case Direction::Forward:
		return "forward";
	case Direction::Backward:
		return "backward"; // TODO: to constant
	case Direction::StandingStill:
		return "standing still";
	default:
		return "";
	}
}