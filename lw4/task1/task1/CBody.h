#pragma once
#include "BodiesException.h"
#include <memory>
#include <string>
#include <iostream>

class CBody
{
public:
	explicit CBody(const std::string& type);
	CBody(CBody const&) = delete;
	virtual ~CBody() = default;
	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	std::string ToString() const;
private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
	std::string m_type;
};

