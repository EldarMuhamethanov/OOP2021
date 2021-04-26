#pragma once
#include "CSolidBody.h"

class CCone: public CSolidBody
{
public:
	CCone(double baseRadius, double height, double density);
	double GetVolume() const override;
	double GetBaseRadius() const;
	double GetHeight() const;
private:
	void AppendProperties(std::ostream& strm) const override;
	double m_baseRadius;
	double m_height;
};

