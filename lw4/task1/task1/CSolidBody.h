#pragma once
#include "CBody.h"

class CSolidBody: public CBody
{
public:
	explicit CSolidBody(const std::string& type, double density);
	double GetDensity() const override;
	double GetVolume() const = 0;
	double GetMass() const override;
private:
	void AppendProperties(std::ostream& strm) const = 0;
	double m_density;
};

