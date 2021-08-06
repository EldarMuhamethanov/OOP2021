#pragma once
#include "IBasicVehicle.h"
#include <memory>

// транспортное средство предназначенное для провозки заданного типа пассажиров
template <typename Passenger>
class IVehicle : public IBasicVehicle
{
public:
	// добавить пассажира на борт
	// т.к. пассажир может быть полиморфным типом, принимаем его по умному указателю
	// Если нет места, выбрасывается ислючение std::logic_error
	virtual void AddPassenger(std::shared_ptr<Passenger> pPassenger) = 0;

	// Получить ссылку на пассажира с заданным индексом
	// выбрасывает исключение std::out_of_range в случае недопустимого индекса
	virtual Passenger const& GetPassenger(size_t index)const = 0;

	// убрать пассажира с заданным индексом
	// выбрасывает исключение std::out_of_range в случае недопустимого индекса
	virtual void RemovePassenger(size_t index) = 0;

};

