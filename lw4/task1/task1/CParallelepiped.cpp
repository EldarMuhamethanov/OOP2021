#include "CParallelepiped.h"

using namespace std;


CParallelepiped::CParallelepiped(double width, double height, double depth, double density)
	: CSolidBody("Parallelepiped", density)
	, m_height(height)
	, m_width(width)
	, m_depth(depth)
{
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetVolume() const
{
	return m_depth * m_width * m_height;
}

void CParallelepiped::AppendProperties(ostream& strm) const
{
	strm << "\twidth = " << GetWidth() << endl;
	strm << "\theight = " << GetHeight() << endl;
	strm << "\tdepth = " << GetDepth() << endl;
}