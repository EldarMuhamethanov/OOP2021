#pragma once
#include <string>

class BodiesException
{
public:
	BodiesException(std::string const& msg);

	std::string GetMessage() const;
private:
	std::string m_msg;
};

