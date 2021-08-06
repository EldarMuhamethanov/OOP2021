#pragma once
#include "CCarImpl.h"
#include "CVehicleImpl.h"
#include "IPoliceCar.h"
#include "IPoliceMan.h"

class CPoliceCar: public CCarImpl<CVehicleImpl<IPoliceCar, IPoliceMan>>
{
public:
	CPoliceCar(MakeOfTheCar carMake, size_t placeCount) : CCarImpl(carMake, placeCount) {}
};

