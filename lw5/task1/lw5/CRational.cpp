#include "CRational.h"
#include <regex>
#include <string>

using namespace std;

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		throw invalid_argument("denominator can't be 0");
	}
	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = abs(m_denominator);
	}
	NormalizeValue();
}

int CRational::GetNumerator()const
{
	return m_numerator;
}

int CRational::GetDenominator()const
{
	return m_denominator;
}

int CRational::GetGreatestCommonFactor(int a, int b)
{
	return b == 0
		? a
		: GetGreatestCommonFactor(b, a % b);
}

int CRational::GetLeastCommonMultiple(int a, int b)
{
	return a * b / GetGreatestCommonFactor(a, b);
}

void CRational::NormalizeValue()
{
	int nod = GetGreatestCommonFactor(abs(m_numerator), m_denominator);
	m_numerator = m_numerator / nod;
	m_denominator = m_denominator / nod;
}

void CRational::AssignValues(int numerator, int denominator)
{
	m_numerator = numerator;
	m_denominator = denominator;

	NormalizeValue();
}

double CRational::ToDouble()const
{
	return (double)m_numerator / (double)m_denominator;
}

pair<int, CRational> CRational::ToCompoundFraction()const
{
	int whole = m_numerator / m_denominator;
	int rationalNumerator = m_numerator % m_denominator;
	return { whole, CRational(rationalNumerator, m_denominator) };
}

CRational const CRational::operator+() const
{
	return *this;
}
CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const operator+(CRational fraction1, CRational const& fraction2)
{
	return fraction1 += fraction2;
}
CRational const operator-(CRational fraction1, CRational const& fraction2)
{
	return fraction1 -= fraction2;
}
CRational const operator*(CRational fraction1, CRational const& fraction2)
{
	return fraction1 *= fraction2;
}
CRational const operator/(CRational fraction1, CRational const& fraction2) 
{
	return fraction1 /= fraction2;
}

CRational& CRational::operator+=(CRational const& fraction)
{
	int nok = GetLeastCommonMultiple(fraction.m_denominator, m_denominator);
	int newFraction1Numerator = int(nok / fraction.m_denominator) * fraction.m_numerator;
	int newFraction2Numerator = int(nok / m_denominator) * m_numerator;

	AssignValues(newFraction1Numerator + newFraction2Numerator, nok);
	return *this;
}

CRational& CRational::operator-=(CRational const& fraction)
{
	int nok = GetLeastCommonMultiple(fraction.m_denominator, m_denominator);
	int newFraction1Numerator = int(nok / m_denominator) * m_numerator;
	int newFraction2Numerator = int(nok / fraction.m_denominator) * fraction.m_numerator;

	AssignValues(newFraction1Numerator - newFraction2Numerator, nok);
	return *this;
}

CRational& CRational::operator*=(CRational const& fraction)
{
	AssignValues(m_numerator * fraction.m_numerator, m_denominator * fraction.m_denominator);
	return *this;
}

CRational& CRational::operator/=(CRational const& fraction)
{
	AssignValues(m_numerator * fraction.m_denominator, m_denominator * fraction.m_numerator);
	return *this;
}

bool operator==(CRational fraction1, CRational const& fraction2)
{
	return ((fraction1.GetNumerator() == fraction2.GetNumerator()) && (fraction1.GetDenominator() == fraction2.GetDenominator()));
}

bool operator!=(CRational fraction1, CRational const& fraction2)
{
	return !(fraction1 == fraction2);
}

bool operator<(CRational const& fraction1, CRational const& fraction2)
{
	return (fraction1.GetNumerator() * fraction2.GetDenominator() < fraction1.GetDenominator() * fraction2.GetNumerator());
}

bool operator>(CRational const& fraction1, CRational const& fraction2)
{
	return !(fraction1 < fraction2) && fraction1 != fraction2;
}

bool operator<=(CRational const& fraction1, CRational const& fraction2)
{
	return !(fraction1 > fraction2);
}

bool operator>=(CRational const& fraction1, CRational const& fraction2)
{
	return !(fraction1 < fraction2);
}

std::ostream& operator<<(std::ostream& stream, CRational const& fraction)
{
	stream << fraction.GetNumerator();
	if (fraction.GetDenominator() != 1)
		stream << "/" << fraction.GetDenominator();
	return stream;
}

std::istream& operator>>(std::istream& stream, CRational& fraction)
{
	string expression;
	if (getline(stream, expression, ' '))
	{
		regex fractionRegex(R"(([\-\+]?\d+)\/?(\d+)?)");
		smatch fractionMatch;
		if (regex_search(expression, fractionMatch, fractionRegex))
		{
			int numerator = stoi(fractionMatch[1]);
			if (fractionMatch[2].matched)
			{
				int denominator = stoi(fractionMatch[2]);
				fraction.AssignValues(numerator, denominator);
				return stream;
			}
			fraction.AssignValues(numerator, 1);
		}
		return stream;
	}
	return stream;
}