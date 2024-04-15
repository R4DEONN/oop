#include "pch.h"
#include "CppUnitTest.h"
#include "../Car/Car.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CarTest
{
	TEST_CLASS(CarTest)
	{
	public:
		
		TEST_METHOD(InitCar)
		{
			Car car{};

			Assert::AreEqual(car.IsTurnedOn(), false);
			Assert::IsTrue(car.GetGear() == Gear::NeutralGear);
			Assert::AreEqual(car.GetSpeed(), 0);
			Assert::IsTrue(car.GetDirection() == Direction::StandingStill);
		}

		TEST_METHOD(NormalBackward)
		{
			Car car{};
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(20);

			Assert::AreEqual(car.IsTurnedOn(), true);
			Assert::IsTrue(car.GetGear() == Gear::ReverseGear);
			Assert::AreEqual(car.GetSpeed(), 20);
			Assert::IsTrue(car.GetDirection() == Direction::Backward);
		}

		TEST_METHOD(SetSpeedAndGearWithEngineOff)
		{
			Car car{};
			car.SetGear(1);
			car.SetSpeed(20);

			Assert::AreEqual(car.IsTurnedOn(), false);
			Assert::IsTrue(car.GetGear() == Gear::NeutralGear);
			Assert::AreEqual(car.GetSpeed(), 0);
		}

		TEST_METHOD(NormalBackwardThenSetGearToNeutralAndThenSetGearToReverse)
		{
			Car car{};
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(20);
			car.SetGear(0);
			car.SetGear(-1);

			Assert::AreEqual(car.IsTurnedOn(), true);
			Assert::IsTrue(car.GetGear() == Gear::NeutralGear);
			Assert::AreEqual(car.GetSpeed(), 20);
			Assert::IsTrue(car.GetDirection() == Direction::Backward);
		}

		TEST_METHOD(TurningOffTheEngineAtANonZeroSpeed)
		{
			Car car{};
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			car.TurnOffEngine();

			Assert::AreEqual(car.IsTurnedOn(), true);
			Assert::IsTrue(car.GetGear() == Gear::LowGear);
			Assert::AreEqual(car.GetSpeed(), 20);
			Assert::IsTrue(car.GetDirection() == Direction::Forward);
		}

		TEST_METHOD(SetForwardGearOnBackwardWithNonZeroSpeed)
		{
			Car car{};
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(20);
			car.SetGear(1);
			Assert::IsTrue(car.GetGear() == Gear::ReverseGear);

			car.SetGear(0);
			car.SetGear(1);
			Assert::IsTrue(car.GetGear() == Gear::NeutralGear);

			car.SetSpeed(0);
			car.SetGear(1);

			Assert::AreEqual(car.IsTurnedOn(), true);
			Assert::IsTrue(car.GetGear() == Gear::LowGear);
			Assert::AreEqual(car.GetSpeed(), 0);
			Assert::IsTrue(car.GetDirection() == Direction::StandingStill);
		}
	};
}
