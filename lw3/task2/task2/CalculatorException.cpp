#include "CalculatorException.h"

using namespace std;

CalculatorException::CalculatorException(string const& message)
	: m_msg(message)
{
}

string CalculatorException::GetMessage() const
{
	return m_msg;
}