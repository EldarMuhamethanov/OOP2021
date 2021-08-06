#pragma once
#include "IVehicle.h"

// марка автомобиля
enum class MakeOfTheCar
{
	BMW,
	MITSUBISHI,
	FORD,
	MERCEDES,
	TOYOTA,
	KIA,
	FERRARI,
	PORSCHE,
	LEXUS,
	NISSAN,
	INIFINITI,
};


// автомобиль, перевозящий заданный тип пассажиров
template <typename Passenger>
class ICar : public IVehicle<Passenger>
{
public:
	virtual MakeOfTheCar GetMakeOfTheCar()const = 0;
};
