#pragma once
#include <string>
#include <iostream>

enum class Direction
{
	Forward,
	Backward,
	StandingStill,
};

enum class Gear
{
	ReverseGear = -1,
	NeutralGear,
	LowGear,
	SecondGear,
	ThirdGear,
	FourthGear,
	FifthGear,
};

class Car
{
public:
	bool IsTurnedOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();

	Gear GetGear() const;
	bool SetGear(int gear);

	int GetSpeed() const;
	bool SetSpeed(int speed);

	Direction GetDirection() const;

private:
	bool m_isTurnedOn = false;
	int m_speed = 0;// m_signedSpeeds
	Gear m_gear = Gear::NeutralGear;
};