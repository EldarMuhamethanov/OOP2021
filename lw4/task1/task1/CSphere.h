#pragma once
#include "CSolidBody.h"

class CSphere: public CSolidBody
{
public:
	CSphere(double radius, double density);
	double GetVolume() const override;
	double GetRadius() const;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_radius;
};

