#pragma once
#include "IPerson.h"

template <typename Base>
class CPersonImpl: public Base
{
public:
	CPersonImpl() = default;
	CPersonImpl(std::string const& name) : m_name(name) {};
	std::string GetName() const
	{
		return m_name;
	}
private:
	std::string m_name = "";
};

