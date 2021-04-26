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

		WHEN("engine is turned off")
		{
			WHEN("change gear with turned off engine")
			{
				REQUIRE_THROWS(car.SetGear(1));
				REQUIRE_THROWS(car.SetGear(-1));
			}

			WHEN("increase speed to 20 with turnedOff engine")
			{
				REQUIRE_THROWS(car.SetSpeed(20));
			}

			WHEN("turn on engine")
			{
				REQUIRE(car.TurnOnEngine());
				REQUIRE(car.IsTurnedOn());
			}
			WHEN("turn off engine")
			{
				REQUIRE(car.TurnOffEngine());
				REQUIRE(!car.IsTurnedOn());
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
					REQUIRE(car.SetGear(1));
					REQUIRE(car.GetGear() == 1);

					REQUIRE(car.SetGear(-1));
					REQUIRE(car.GetGear() == -1);

					REQUIRE_THROWS(car.SetGear(2));
				}
				WHEN("increase speed to 20 with turnedOn engine BUT on neutral gear")
				{
					REQUIRE_THROWS(car.SetSpeed(20));
				}
			}

			WHEN("use first gear")
			{
				car.SetGear(1);
				WHEN("change gear with turnedOn engine, gear = 1, speed = 25")
				{
					car.SetSpeed(25);
					REQUIRE(car.SetGear(2));
					REQUIRE(car.GetGear() == 2);

					REQUIRE_THROWS(car.SetGear(-1));

					REQUIRE(car.SetGear(2));
					REQUIRE(car.GetGear() == 2);
				}
			}

			WHEN("use back gear")
			{
				car.SetGear(-1);
				WHEN("increase speed with turnedOn engine and on back gear")
				{
					REQUIRE(car.SetSpeed(10));
					REQUIRE(car.GetSpeed() == -10);

					REQUIRE_THROWS(car.SetSpeed(30));
				}
				WHEN("have any speed")
				{
					car.SetSpeed(10);
					WHEN("change gear")
					{
						REQUIRE_THROWS(car.SetGear(1));

						REQUIRE(car.SetGear(0));
						REQUIRE(car.GetGear() == 0);
					}
				}
				WHEN("speed = 0")
				{
					car.SetSpeed(0);
					WHEN("change gear")
					{
						REQUIRE(car.SetGear(1));
						REQUIRE(car.GetGear() == 1);

						REQUIRE_THROWS(car.SetGear(2));
					}
				}
			}
		}

		WHEN("car has turnedOn engine speed or/and gear != 0")
		{
			car.TurnOnEngine();
			WHEN("turn off engine and check value")
			{
				REQUIRE(car.TurnOffEngine());
				REQUIRE(!car.IsTurnedOn());
			}
			WHEN("car has speed or gear")
			{
				car.SetGear(1);
				car.SetSpeed(10);
				WHEN("try to turn off engine and catch error")
				{
					REQUIRE_THROWS(car.TurnOffEngine());
				}
				car.SetGear(0);
				WHEN("try to turn off engine and catch error")
				{
					REQUIRE_THROWS(car.TurnOffEngine());
				}
			}
		}
		WHEN("car has turnOn engine any speed and first gear")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(10);
			WHEN("turn to neutral gear")
			{
				car.SetGear(0);
				WHEN("try to turn to first gear and catch error")
				{
					REQUIRE_THROWS(car.SetGear(1));
				}
			}
		}
	}
}