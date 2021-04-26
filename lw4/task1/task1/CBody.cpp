#include "CBody.h"
#include <sstream>
#include <iomanip>

using namespace std;

CBody::CBody(const string& type)
	: m_type(type)
{
}

string CBody::ToString()const
{
	ostringstream strm;
	strm << m_type << ":" << endl << setprecision(10)
		<< "\tdensity = " << GetDensity() << endl
		<< "\tvolume = " << GetVolume() << endl
		<< "\tmass = " << GetMass() << endl;
	AppendProperties(strm);
	return strm.str();
}
