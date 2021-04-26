#include "CCompound.h"

using namespace std;

CCompound::CCompound()
	: CBody("Compound")
{
}

double CCompound::GetMass() const
{
	double sum = 0;
	for (const auto& childBody : m_childBodies)
	{
		sum += childBody->GetMass();
	}
	return sum;
}

double CCompound::GetVolume() const
{
	double sum = 0;
	for (const auto& childBody : m_childBodies)
	{
		sum += childBody->GetVolume();
	}
	return sum;
}

double CCompound::GetDensity() const
{
	double volume = GetVolume();
	return volume != 0
		? GetMass() / GetVolume()
		: 0;
}

vector<shared_ptr<CBody>> CCompound::GetChildBodies() const
{
	return m_childBodies;
}

void CCompound::AppendProperties(std::ostream& strm) const
{
	strm << "\tincludes bodies: "<< endl;
	strm << endl;
	for (const auto child : m_childBodies)
	{
		string childInfo = child->ToString();
		strm << "\t" << childInfo << endl;
	}
}

bool CCompound::CheckExistCompoundBodyInBody(vector<shared_ptr<CBody>> const& childs) const
{
	for (const auto child : childs)
	{
		shared_ptr<CCompound> compoundChild = dynamic_pointer_cast<CCompound>(child);
		if (compoundChild == nullptr)
			continue;
		if (compoundChild.get() == this)
			return true;
		if (CheckExistCompoundBodyInBody(compoundChild.get()->GetChildBodies()))
			return true;
	}
	return false;
}

bool CCompound::CheckExistBodyInCompoundBody(shared_ptr<CBody> const& child) const
{
	for (const auto childsItem : m_childBodies)
	{
		if (child == childsItem)
		{
			return true;
		}
	}
	return false;
}

bool CCompound::AddChildBody(shared_ptr<CBody> const& child)
{
	shared_ptr<CSolidBody> solidChild = dynamic_pointer_cast<CSolidBody>(child);
	if (solidChild != nullptr)
	{
		AddChildSolidBody(solidChild);
		return true;
	}
	shared_ptr<CCompound> compoundChild = dynamic_pointer_cast<CCompound>(child);
	if (compoundChild != nullptr)
	{
		AddChildCompoundBody(compoundChild);
		return true;
	}
	throw BodiesException("unknown child class");
}

bool CCompound::AddChildCompoundBody(shared_ptr<CCompound> const& compoundChild)
{
	if (compoundChild.get() == this || CheckExistCompoundBodyInBody(compoundChild->GetChildBodies()))
	{
		throw BodiesException("recursive append");
	}
	m_childBodies.push_back(compoundChild);
	return true;
}

bool CCompound::AddChildSolidBody(shared_ptr<CSolidBody> const& child)
{
	if (CheckExistBodyInCompoundBody(child))
	{
		throw BodiesException("body already exist in compound body");
	}
	m_childBodies.push_back(child);
	return true;
}