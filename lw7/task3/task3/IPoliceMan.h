#pragma once
#include "IPerson.h"

class IPoliceMan: public IPerson
{
public:
	// название полицейского департамента
	virtual std::string GetDepartmentName()const = 0;

};

