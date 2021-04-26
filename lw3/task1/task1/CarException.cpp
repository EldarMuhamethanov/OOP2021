#include "CarException.h"

using namespace std;

CarException::CarException(string const& message)
	: m_msg(message)
{
}

string CarException::GetMessage() const
{
	return m_msg;
}