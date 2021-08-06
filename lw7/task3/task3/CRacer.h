#pragma once
#include "CPersonImpl.h"
#include "IRacer.h"

class CRacer: public CPersonImpl<IRacer>
{
public:
	CRacer(std::string name, size_t avardsCount)
		: CPersonImpl<IRacer>(name)
		, m_avardsCount(avardsCount)
	{}
	size_t GetAwardsCount()const
	{
		return m_avardsCount;
	}
private:
	size_t m_avardsCount;
};

