#pragma once
#include "CPersonImpl.h"
#include "IPoliceMan.h"

class CPoliceMan: public CPersonImpl<IPoliceMan>
{
public:
	CPoliceMan(std::string name, std::string departmentName)
		: CPersonImpl<IPoliceMan>(name)
		, m_departmentName(departmentName)
	{}
	std::string GetDepartmentName()const
	{
		return m_departmentName;
	}
private:
	std::string m_departmentName;
};

