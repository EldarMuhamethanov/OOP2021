#pragma once
#include "CCarImpl.h"
#include "CVehicleImpl.h"
#include "IRacingCar.h"
#include "IRacer.h"

class CRacingCar: public CCarImpl<CVehicleImpl<IRacingCar, IRacer>>
{
public:
	CRacingCar(MakeOfTheCar carMake, size_t placeCount): CCarImpl(carMake, placeCount) {}
};

