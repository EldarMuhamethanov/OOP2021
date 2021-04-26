#pragma once
#include <iostream>
#include <fstream>

class CRational
{
public:
	CRational();

	CRational(int value);

	CRational(int numerator, int denominator);

	int GetNumerator()const;

	int GetDenominator()const;

	double ToDouble()const;

	CRational const operator+() const;
	CRational const operator-() const;
	
	CRational& operator +=(CRational const& fraction);
	CRational& operator -=(CRational const& fraction);
	CRational& operator *=(CRational const& fraction);
	CRational& operator /=(CRational const& fraction);

	friend std::istream& operator>>(std::istream& stream, CRational& fraction);
	friend std::ostream& operator<<(std::ostream& stream, CRational const& fraction);

	std::pair<int, CRational> ToCompoundFraction()const;

private:
	void NormalizeValue();
	void AssignValues(int numerator, int denominator);
	int GetLeastCommonMultiple(int a, int b);
	int GetGreatestCommonFactor(int a, int b);

	int m_numerator;
	int m_denominator;
};


CRational const operator+(CRational fraction1, CRational const& fraction2);
CRational const operator-(CRational fraction1, CRational const& fraction2);
CRational const operator*(CRational fraction1, CRational const& fraction2);
CRational const operator/(CRational fraction1, CRational const& fraction2);

bool operator==(CRational fraction1, CRational const& fraction2);
bool operator!=(CRational fraction1, CRational const& fraction2);

bool operator<(CRational const& fraction1, CRational const& fraction2);
bool operator>(CRational const& fraction1, CRational const& fraction2);
bool operator<=(CRational const& fraction1, CRational const& fraction2);
bool operator>=(CRational const& fraction1, CRational const& fraction2);