#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task3/CPoliceCar.h"
#include "../task3/CTaxi.h"
#include "../task3/CPoliceMan.h"
#include "../task3/CRacer.h"
#include "../task3/CPerson.h"

using namespace std;

SCENARIO("scenario 1")
{
	CPoliceMan policeMan1("Джон Смит", "Северо-западный полицейский участок");
	CPoliceCar policeCar(MakeOfTheCar::FORD, 5);

	policeCar.AddPassenger(make_shared<CPoliceMan>(policeMan1));

	CPoliceMan policeMan2("Джим Кларк", "Юго-восточный полицейский участок");

	policeCar.AddPassenger(make_shared<CPoliceMan>(policeMan2));

	REQUIRE(policeMan1.GetName() == "Джон Смит");
	REQUIRE(policeMan1.GetDepartmentName() == "Северо-западный полицейский участок");
	REQUIRE(policeMan2.GetName() == "Джим Кларк");
	REQUIRE(policeMan2.GetDepartmentName() == "Юго-восточный полицейский участок");

	REQUIRE(policeCar.GetMakeOfTheCar() == MakeOfTheCar::FORD);
	REQUIRE(policeCar.GetPassengerCount() == 2);
	REQUIRE(policeCar.GetPassenger(0).GetName() == "Джон Смит");
	REQUIRE(policeCar.GetPassenger(1).GetName() == "Джим Кларк");

	/////////////////////////////////////////////////////////////////////////////////////

	policeCar.RemovePassenger(1);
	REQUIRE(policeCar.GetPassengerCount() == 1);

	CTaxi taxi(MakeOfTheCar::TOYOTA, 2);
	CPerson taxiDriver("Раджа Ганди");
	CRacer racer("Михаэля Шумахера", 20);

	REQUIRE(taxi.GetMakeOfTheCar() == MakeOfTheCar::TOYOTA);
	REQUIRE(taxiDriver.GetName() == "Раджа Ганди");
	REQUIRE(racer.GetName() == "Михаэля Шумахера");
	REQUIRE(racer.GetAwardsCount() == 20);

	taxi.AddPassenger(make_shared<CPerson>(taxiDriver));
	taxi.AddPassenger(make_shared<CRacer>(racer));

	REQUIRE(taxi.GetPassengerCount() == 2);
	
	REQUIRE(taxi.GetPassenger(0).GetName() == "Раджа Ганди");
	REQUIRE(taxi.GetPassenger(1).GetName() == "Михаэля Шумахера");

	taxi.RemovePassenger(0);
	REQUIRE(taxi.GetPassengerCount() == 1);
	taxi.AddPassenger(make_shared<CPoliceMan>(policeMan2));

	REQUIRE(taxi.GetPassenger(0).GetName() == "Михаэля Шумахера");
	REQUIRE(taxi.GetPassenger(1).GetName() == "Джим Кларк");
	REQUIRE(taxi.GetPassengerCount() == 2);

	//////////////////////////////////////////////////////////////////////////

	try
	{
		taxi.AddPassenger(make_shared<CPerson>(taxiDriver));
		REQUIRE(false);
	}
	catch (const logic_error& e)
	{
		REQUIRE(e.what() == "vehicle is full"s);
	}
}