#pragma once
#include "CVehicleImpl.h"
#include "IBus.h"
#include "IPerson.h"

class CBus: public CVehicleImpl<IBus, IPerson>
{
public:
	CBus(size_t placeCount) : CVehicleImpl(placeCount) {};
};

