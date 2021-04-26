#include "CCone.h"

using namespace std;


CCone::CCone(double baseRadius, double height, double density)
	: CSolidBody("Cone", density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
}

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return pow(m_baseRadius, 2) * 3.14 * m_height / 3;
}

void CCone::AppendProperties(ostream& strm) const
{
	strm << "\tbase radius= " << GetBaseRadius() << endl;
	strm << "\theight= " << GetHeight() << endl;
}