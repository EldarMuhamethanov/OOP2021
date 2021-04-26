#include "CSphere.h"

using namespace std;

CSphere::CSphere(double radius, double density)
	: CSolidBody("sphere", density)
	, m_radius(radius)
{
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const 
{
	return pow(m_radius, 3) * 4 / 3 * 3.14;
}

void CSphere::AppendProperties(ostream& strm) const
{
	strm << "\tradius = " << GetRadius() << endl;
}
