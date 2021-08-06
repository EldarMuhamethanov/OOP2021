#pragma once
#include "ICar.h"

template <typename Base>
class CCarImpl: public Base
{
public:
	CCarImpl(MakeOfTheCar make, size_t placeCount)
		: Base(placeCount)
		, m_carMake(make)
	{
	}

	MakeOfTheCar GetMakeOfTheCar() const
	{
		return m_carMake;
	}

private:
	MakeOfTheCar m_carMake;
};

