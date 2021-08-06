#include "CSolidBody.h"

using namespace std;


CSolidBody::CSolidBody(const string& type, double density)
	: CBody(type)
	, m_density(density < 0 ? 0 :density)
	, m_parentBody(nullptr)
{
}

CSolidBody::~CSolidBody()
{
	m_parentBody = nullptr;
}

void CSolidBody::SetParentBody(CBody* body)
{
	m_parentBody = body;
}

CBody* CSolidBody::GetParentBody()
{
	return m_parentBody;
}

double CSolidBody::GetDensity() const
{
	return m_density;
}

double CSolidBody::GetMass() const
{
	return GetVolume() * GetDensity();
}