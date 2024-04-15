#include "./Car.h"
#include <iostream>
#include <map>

struct SpeedRange
{
	int m_minSpeed;
	int m_maxSpeed;

	SpeedRange()
		: m_minSpeed(0)
		, m_maxSpeed(0)
	{};

	SpeedRange(int minSpeed, int maxSpeed)
		: m_minSpeed(minSpeed)
		, m_maxSpeed(maxSpeed)
	{}
};

std::map<Gear, SpeedRange> GearSpeedRanges = {
	{Gear::ReverseGear, {-20, 0}},
	{Gear::NeutralGear, {INT_MIN, INT_MAX}},
	{Gear::LowGear, {0, 30}},
	{Gear::SecondGear, {20, 50}},
	{Gear::ThirdGear, {30, 60}},
	{Gear::FourthGear, {40, 90}},
	{Gear::FifthGear, {50, 150}},
};

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

bool Car::TurnOnEngine()
{
	m_isTurnedOn = true;
	return m_isTurnedOn;
}

bool Car::TurnOffEngine()
{
	if (m_gear == Gear::NeutralGear && m_speed == 0)
	{
		m_isTurnedOn = false;
	}

	return !m_isTurnedOn;
}

Gear Car::GetGear() const
{
	return m_gear;
}

bool Car::SetGear(int gear)
{
	if (!IsTurnedOn())
	{
		return false;
	}
	auto newGear = static_cast<Gear>(gear);

	if (newGear == Gear::ReverseGear && m_speed != 0)
	{
		return false;
	}

	auto speedRange = GearSpeedRanges[newGear];
	if (m_speed >= speedRange.m_minSpeed && m_speed <= speedRange.m_maxSpeed)
	{
		m_gear = newGear;
		return true;
	}

	return false;
}

int Car::GetSpeed() const
{
	return std::abs(m_speed);
}

bool Car::SetSpeed(int speed)
{
	if (!IsTurnedOn())
	{
		return false;
	}

	if (m_gear == Gear::ReverseGear || m_speed < 0)
	{
		speed *= -1;
	}

	//TODO функция
	if (m_gear == Gear::NeutralGear)
	{
		if (std::abs(speed) <= std::abs(m_speed))
		{
			m_speed = speed;
			return true;
		}

		return false;
	}

	auto speedRange = GearSpeedRanges[m_gear];
	if (speed > speedRange.m_maxSpeed)
	{
		m_speed = speedRange.m_maxSpeed;
	}
	else if (speed < speedRange.m_minSpeed)
	{
		m_speed = speedRange.m_minSpeed;
	}
	else
	{
		m_speed = speed;
	}

	return true;
}

Direction Car::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	
	if (m_speed == 0)
	{
		return Direction::StandingStill;
	}

	if (m_speed < 0)
	{
		return Direction::Backward;
	}
}