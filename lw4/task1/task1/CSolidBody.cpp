#include "CSolidBody.h"

using namespace std;


CSolidBody::CSolidBody(const string& type, double density)
	: CBody(type)
	, m_density(density < 0 ? 0 :density)
{
}

double CSolidBody::GetDensity() const
{
	return m_density;
}

double CSolidBody::GetMass() const
{
	return GetVolume() * GetDensity();
}