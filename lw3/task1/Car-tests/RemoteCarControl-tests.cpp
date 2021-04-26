#include "../../../Catch2/catch.hpp"
#include "../task1/RemoteCarControl.h"
#include <sstream>

using namespace std;

SCENARIO("RemoteCarControl tests")
{
	GIVEN("created car")
	{
		Car car;
		WHEN("Car has any speed, any gear")
		{
			istringstream in("Info");
			ostringstream out("");
			string infoResult = "Состояние двигателя: Выключен\nВключенная передача: Нейтральная\nТекущая скорость: 0\nНаправление движения: Стоит на месте\n\n";
			RemoteCarControl RemoteCarControl(car, in, out);
			REQUIRE(RemoteCarControl.HandleCommand());
			REQUIRE(out.str() == infoResult);
		}
		WHEN("Input EngineOn then input EngineOff")
		{
			istringstream in("EngineOn\nEngineOff");
			ostringstream out("");
			RemoteCarControl RemoteCarControl(car, in, out);
			REQUIRE(RemoteCarControl.HandleCommand());
			REQUIRE(RemoteCarControl.HandleCommand());
			REQUIRE(out.str() == "Двигатель включен\nДвигатель выключен\n");
		}
		WHEN("Car Engine is off")
		{
			WHEN("Input Set Speed")
			{
				istringstream in("SetSpeed 10");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Ошибка: Нельзя изменить скорость с выключенным двигателем\n");
			}
			WHEN("Input Set Gear")
			{
				istringstream in("SetGear 1");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Ошибка: Двигатель не включен или введена некорректная передача\n");
			}
		}
		WHEN("Car Engine Is On")
		{
			car.TurnOnEngine();
			WHEN("Set gear 1")
			{
				istringstream in("SetGear 1");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Передача сейчас 1\n");
			}
			WHEN("Set gear 2")
			{
				istringstream in("SetGear 2");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Ошибка: На текущей скорости 0 на передачу 2 невозможно\n");
			}
			WHEN("Set Speed 10")
			{
				istringstream in("SetSpeed 10");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Ошибка: Нельзя увеличивать скорость на нейтральной передаче\n");
			}
			WHEN("car has 1 gear, then set speed 10")
			{
				car.SetGear(1);
				istringstream in("SetSpeed 10");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Скорость сейчас 10\n");
			}
			WHEN("car has 1 gear, then set speed 31")
			{
				car.SetGear(1);
				istringstream in("SetSpeed 31");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Ошибка: На передаче 1 введенная скорость недопустима\n");
			}
			WHEN("car has gear 1 and speed 15, input set gear 3")
			{
				car.SetGear(1);
				car.SetSpeed(15);
				istringstream in("SetGear 3");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "Ошибка: На текущей скорости 15 на передачу 3 невозможно\n");
			}
			WHEN("car has any speed and neutral gear")
			{
				car.SetGear(1);
				car.SetSpeed(15);
				car.SetGear(0);
				WHEN("Input Set Gear 1")
				{
					istringstream in("SetGear 1");
					ostringstream out("");
					RemoteCarControl RemoteCarControl(car, in, out);
					REQUIRE(!RemoteCarControl.HandleCommand());
					REQUIRE(out.str() == "Ошибка: С нейтральной передачи нельзя переключиться на другую на ходу\n");
				}
				WHEN("Set Speed 0 and then set gear 1")
				{
					car.SetSpeed(0);
					istringstream in("SetGear 1");
					ostringstream out("");
					RemoteCarControl RemoteCarControl(car, in, out);
					REQUIRE(RemoteCarControl.HandleCommand());
					REQUIRE(out.str() == "Передача сейчас 1\n");
				}
			}
			WHEN("car has gear != 0")
			{
				car.SetGear(1);
				car.SetSpeed(15);
				WHEN("Input EngineOff")
				{
					istringstream in("EngineOff");
					ostringstream out("");
					RemoteCarControl RemoteCarControl(car, in, out);
					REQUIRE(!RemoteCarControl.HandleCommand());
					REQUIRE(out.str() == "Ошибка: Невозможно выключить двигатель, потому что машина в движении или передача не нейтральная\n");
				}
			}
		}
		WHEN("Car has any speed, any gear")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(15);
			istringstream in("Info");
			ostringstream out("");
			string infoResult = "Состояние двигателя: Включен\nВключенная передача: Первая\nТекущая скорость: 15\nНаправление движения: Вперед\n\n";
			RemoteCarControl RemoteCarControl(car, in, out);
			REQUIRE(RemoteCarControl.HandleCommand());
			REQUIRE(out.str() == infoResult);
		}
		WHEN("Car has any speed, any gear")
		{
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(15);
			istringstream in("Info");
			ostringstream out("");
			string infoResult = "Состояние двигателя: Включен\nВключенная передача: Задний ход\nТекущая скорость: 15\nНаправление движения: Назад\n\n";
			RemoteCarControl RemoteCarControl(car, in, out);
			REQUIRE(RemoteCarControl.HandleCommand());
			REQUIRE(out.str() == infoResult);
		}
		WHEN("Input unknown command")
		{
			istringstream in("Unknown");
			ostringstream out("");
			RemoteCarControl RemoteCarControl(car, in, out);
			REQUIRE(!RemoteCarControl.HandleCommand());
		}
	}
}
