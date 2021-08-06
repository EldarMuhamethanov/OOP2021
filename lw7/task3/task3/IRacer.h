#pragma once
#include "IPerson.h"

class IRacer: public IPerson
{
public:
	// количество наград 
	virtual size_t GetAwardsCount()const = 0;
};

