#pragma once
#include <string>


class CalculatorException
{
public:
	CalculatorException(std::string const& msg);

	std::string GetMessage() const;
private:
	std::string m_msg;
};

