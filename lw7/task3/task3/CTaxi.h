#pragma once
#include "CCarImpl.h"
#include "CVehicleImpl.h"
#include "ITaxi.h"
#include "IPerson.h"

class CTaxi: public CCarImpl<CVehicleImpl<ITaxi, IPerson>>
{
public:
	CTaxi(MakeOfTheCar carMake, size_t placeCount): CCarImpl(carMake, placeCount) {}
};
