#pragma once
#include "CSolidBody.h"

class CCylinder: public CSolidBody
{
public:
	CCylinder(double baseRadius, double height, double density);
	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
private:
	void AppendProperties(std::ostream& strm) const override;
	double m_baseRadius;
	double m_height;
};

