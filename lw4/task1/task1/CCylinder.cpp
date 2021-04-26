#include "CCylinder.h"

using namespace std;

CCylinder::CCylinder(double baseRadius, double height, double density)
	: CSolidBody("Cylinder", density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return pow(m_baseRadius, 2) * 3.14 * m_height;
}

void CCylinder::AppendProperties(ostream& strm) const
{
	strm << "\tbase radius= " << GetBaseRadius() << endl;
	strm << "\theight= " << GetHeight() << endl;
}