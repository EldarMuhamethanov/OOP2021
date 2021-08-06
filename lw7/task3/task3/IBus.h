#pragma once
#include "IVehicle.h"
#include "IPerson.h"

// марка автобуса
class IBus : public IVehicle<IPerson>
{

};
