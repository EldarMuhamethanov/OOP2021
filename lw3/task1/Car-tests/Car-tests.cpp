#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task1/Car.h"

SCENARIO("Car test")
{
	GIVEN("created Car")
	{
		Car car;
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Direction::STAY);

		WHEN("engine is turned off")
		{
			WHEN("change gear with turned off engine")
			{
				bool isSuccess;
				isSuccess = car.SetGear(1);
				THEN("Error")
				{
					REQUIRE(!isSuccess);
				}
				isSuccess = car.SetGear(-1);
				THEN("Error")
				{
					REQUIRE(!isSuccess);
				}
			}

			WHEN("increase speed to 20 with turnedOff engine")
			{
				bool isSuccess = car.SetSpeed(20);
				THEN("Error")
				{
					REQUIRE(!isSuccess);
				}
			}

			WHEN("turn on engine")
			{
				bool isSuccess = car.TurnOnEngine();
				THEN("Success")
				{
					REQUIRE(isSuccess);
					REQUIRE(car.IsTurnedOn());
				}
			}
			WHEN("turn off engine")
			{
				bool isSuccess = car.TurnOffEngine();
				THEN("Success")
				{
					REQUIRE(isSuccess);
					REQUIRE(!car.IsTurnedOn());
				}
			}
		}

		WHEN("engine is turned on")
		{
			car.TurnOnEngine();
			WHEN("use neutral gear")
			{
				car.SetGear(0);
				WHEN("change gear with turnedOn engine, neutral gear and speed = 0")
				{
					bool isSuccess;
					isSuccess = car.SetGear(1);
					THEN("Success")
					{
						REQUIRE(isSuccess);
						REQUIRE(car.GetGear() == 1);
					}
					isSuccess = car.SetGear(-1);
					THEN("Success")
					{
						REQUIRE(isSuccess);
						REQUIRE(car.GetGear() == -1);
					}
					isSuccess = car.SetGear(2);
					THEN("Error")
					{
						REQUIRE(!isSuccess);
					}
				}
				WHEN("increase speed to 20 with turnedOn engine BUT on neutral gear")
				{
					bool isSuccess = car.SetSpeed(20);
					THEN("Error")
					{
						REQUIRE(!isSuccess);
					}
				}
			}

			WHEN("use first gear")
			{
				car.SetGear(1);
				WHEN("change gear with turnedOn engine, gear = 1, speed = 25")
				{
					car.SetSpeed(25);
					REQUIRE(car.GetDirection() == Direction::FORWARD);
					bool isSuccess = car.SetGear(2);
					THEN("Success")
					{
						REQUIRE(isSuccess);
						REQUIRE(car.GetGear() == 2);
					}
					isSuccess = car.SetGear(-1);
					THEN("Error")
					{
						REQUIRE(!isSuccess);
					}
					isSuccess = car.SetGear(2);
					THEN("Sucess")
					{
						REQUIRE(isSuccess);
						REQUIRE(car.GetGear() == 2);
					}
				}
			}

			WHEN("use back gear")
			{
				car.SetGear(-1);
				REQUIRE(car.GetDirection() == Direction::STAY);
				WHEN("increase speed with turnedOn engine and on back gear")
				{
					bool isSuccess = car.SetSpeed(10);
					THEN("Success")
					{
						REQUIRE(isSuccess);
						REQUIRE(car.GetSpeed() == 10);
						REQUIRE(car.GetDirection() == Direction::BACK);
					}
					isSuccess = car.SetSpeed(30);
					THEN("Error")
					{
						REQUIRE(!isSuccess);
					}
				}
				WHEN("have any speed")
				{
					car.SetSpeed(10);
					WHEN("change gear")
					{
						bool isSuccess = car.SetGear(1);
						THEN("Error")
						{
							REQUIRE(!isSuccess);
						}
						isSuccess = car.SetGear(0);
						THEN("Sucess")
						{
							REQUIRE(isSuccess);
							REQUIRE(car.GetGear() == 0);
						}
					}
				}
				WHEN("speed = 0")
				{
					car.SetSpeed(0);
					REQUIRE(car.GetDirection() == Direction::STAY);
					WHEN("change gear")
					{
						bool isSuccess = car.SetGear(1);
						THEN("Success")
						{
							REQUIRE(isSuccess);
							REQUIRE(car.GetGear() == 1);
						}
						isSuccess = car.SetGear(2);
						THEN("Error")
						{
							REQUIRE(!isSuccess);
						}
					}
				}
			}
		}

		WHEN("car has turnedOn engine speed or/and gear != 0")
		{
			car.TurnOnEngine();
			WHEN("car has speed or gear")
			{
				car.SetGear(1);
				car.SetSpeed(10);
				WHEN("turn off engine")
				{
					bool isSuccess = car.TurnOffEngine();
					THEN("error")
					{
						REQUIRE(!isSuccess);
					}
				}
				car.SetGear(0);
				WHEN("turn off engine")
				{
					bool isSuccess = car.TurnOffEngine();
					THEN("error")
					{
						REQUIRE(!isSuccess);
					}
				}
			}
			WHEN("car does not have gear or speed")
			{
				WHEN("turn off engine")
				{
					bool isSuccess = car.TurnOffEngine();
					THEN("Success")
					{
						REQUIRE(isSuccess);
					}
				}
			}
		}
	}
}