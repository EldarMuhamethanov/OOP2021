#include "BodiesException.h"

using namespace std;

BodiesException::BodiesException(string const& message)
	: m_msg(message)
{
}

string BodiesException::GetMessage() const
{
	return m_msg;
}