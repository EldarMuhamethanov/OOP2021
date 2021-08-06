#pragma once
#include "CPersonImpl.h"
#include "IPerson.h"

class CPerson: public CPersonImpl<IPerson>
{
public:
	CPerson(std::string name): CPersonImpl(name) {}
};

