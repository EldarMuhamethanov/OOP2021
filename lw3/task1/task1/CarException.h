#pragma once
#include <exception>
#include <string>

class CarException : std::exception
{
public:
	CarException(std::string const& msg);

	std::string GetMessage() const;
private:
	std::string m_msg;
};