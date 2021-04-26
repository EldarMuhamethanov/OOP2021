#pragma once
#include "CBody.h"
#include "CSolidBody.h"
#include <vector>

class CCompound: public CBody
{
public:
	CCompound();
	bool AddChildBody(std::shared_ptr<CBody> const& child);
	
	std::vector<std::shared_ptr<CBody>> GetChildBodies() const;

	double GetDensity() const override;
	double GetVolume() const override;
	double GetMass() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	bool CheckExistCompoundBodyInBody(std::vector<std::shared_ptr<CBody>> const& childs) const;
	bool CheckExistBodyInCompoundBody(std::shared_ptr<CBody> const& child) const;
	bool AddChildCompoundBody(std::shared_ptr<CCompound> const& compoundChild);
	bool AddChildSolidBody(std::shared_ptr<CSolidBody> const& child);
	std::vector<std::shared_ptr<CBody>> m_childBodies;
};

