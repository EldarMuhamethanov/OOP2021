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
			string infoResult = "��������� ���������: ��������\n���������� ��������: �����������\n������� ��������: 0\n����������� ��������: ����� �� �����\n\n";
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
			REQUIRE(out.str() == "��������� �������\n��������� ��������\n");
		}
		WHEN("Car Engine is off")
		{
			WHEN("Input Set Speed")
			{
				istringstream in("SetSpeed 10");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "������: ������ �������� �������� � ����������� ����������\n");
			}
			WHEN("Input Set Gear")
			{
				istringstream in("SetGear 1");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "������: ��������� �� ������� ��� ������� ������������ ��������\n");
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
				REQUIRE(out.str() == "�������� ������ 1\n");
			}
			WHEN("Set gear 2")
			{
				istringstream in("SetGear 2");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "������: �� ������� �������� 0 �� �������� 2 ����������\n");
			}
			WHEN("Set Speed 10")
			{
				istringstream in("SetSpeed 10");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "������: ������ ����������� �������� �� ����������� ��������\n");
			}
			WHEN("car has 1 gear, then set speed 10")
			{
				car.SetGear(1);
				istringstream in("SetSpeed 10");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "�������� ������ 10\n");
			}
			WHEN("car has 1 gear, then set speed 31")
			{
				car.SetGear(1);
				istringstream in("SetSpeed 31");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "������: �� �������� 1 ��������� �������� �����������\n");
			}
			WHEN("car has gear 1 and speed 15, input set gear 3")
			{
				car.SetGear(1);
				car.SetSpeed(15);
				istringstream in("SetGear 3");
				ostringstream out("");
				RemoteCarControl RemoteCarControl(car, in, out);
				REQUIRE(!RemoteCarControl.HandleCommand());
				REQUIRE(out.str() == "������: �� ������� �������� 15 �� �������� 3 ����������\n");
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
					REQUIRE(out.str() == "������: � ����������� �������� ������ ������������� �� ������ �� ����\n");
				}
				WHEN("Set Speed 0 and then set gear 1")
				{
					car.SetSpeed(0);
					istringstream in("SetGear 1");
					ostringstream out("");
					RemoteCarControl RemoteCarControl(car, in, out);
					REQUIRE(RemoteCarControl.HandleCommand());
					REQUIRE(out.str() == "�������� ������ 1\n");
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
					REQUIRE(out.str() == "������: ���������� ��������� ���������, ������ ��� ������ � �������� ��� �������� �� �����������\n");
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
			string infoResult = "��������� ���������: �������\n���������� ��������: ������\n������� ��������: 15\n����������� ��������: ������\n\n";
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
			string infoResult = "��������� ���������: �������\n���������� ��������: ������ ���\n������� ��������: 15\n����������� ��������: �����\n\n";
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
