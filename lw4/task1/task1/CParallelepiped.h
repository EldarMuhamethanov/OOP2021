#pragma once
#include "CSolidBody.h"

class CParallelepiped : public CSolidBody
{
public:
	CParallelepiped(double width, double height, double depth, double density);
	double GetWidth() const;
	double GetVolume() const override;
	double GetHeight() const;
	double GetDepth() const;
private:
	void AppendProperties(std::ostream& strm) const override;
	double m_width;
	double m_height;
	double m_depth;
};

