#include "BodiesContainer.h"
#include <sstream>

const double ACCELERATION_OF_GRAVITY = 9.8;
const double DENSITY_OF_WATER = 1000;

using namespace std;
using namespace std::placeholders;

BodiesContainer::BodiesContainer(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "add", bind(&BodiesContainer::AddBody, this, _1) },
		{ "append", bind(&BodiesContainer::AppendBodyToCompoundBody, this, _1) },
		{ "info", bind(&BodiesContainer::Info, this, _1) },
	})
{
}

bool BodiesContainer::HandleCommand() const
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	m_output << "Error: unknown command" << endl;
	return false;
}

bool BodiesContainer::Info(istream&)
{
	if (m_nameToBodiesMap.size() > 0)
	{
		for (const auto& mapItem : m_nameToBodiesMap)
		{
			m_output << "Body with name " << mapItem.first << endl;
			m_output << mapItem.second.get()->ToString() << endl;
		}
		m_output << "Body with biggest mass: " << endl;
		PrintBodyWithBiggestMass();
		m_output << "Body with biggest Arhimed power: " << endl;
		PrintBodyWithBiggestArhimedPower();
		return true;
	}
	m_output << "no one body was added" << endl;
	return false;
}

bool BodiesContainer::AppendBodyToCompoundBody(istream& args)
{
	string addedBodyName;
	string parentBodyName;
	string to;
	args >> addedBodyName >> to >> parentBodyName;

	if (!CheckExistBody(addedBodyName))
	{
		m_output << "Error: body with name \"" << addedBodyName << "\" does not exist" << endl;
		return false;
	}
	if (!CheckExistBody(parentBodyName))
	{
		m_output << "Error: body with name \"" << parentBodyName << "\" does not exist" << endl;
		return false;
	}
	shared_ptr<CCompound> parentBody = dynamic_pointer_cast<CCompound>(GetBodyByName(parentBodyName));

	if (parentBody == nullptr)
	{
		m_output << "Error: body with name \"" << parentBodyName << "\" is not compound" << endl;
		return false;
	}
	try
	{
		parentBody->AddChildBody(GetBodyByName(addedBodyName));
		return true;
	}
	catch (const BodiesException& exception)
	{
		ExceptionHandler(exception);
		return false;
	}
}

bool BodiesContainer::AddBody(istream& args)
{
	string bodyType;
	args >> bodyType;
	if (bodyType == "solid")
	{
		string solidBodyType;
		string solidBodyName;
		args >> solidBodyType >> solidBodyName;
		if (CheckExistBody(solidBodyName))
		{
			m_output << "Error: Bodies with name \"" << solidBodyName << "\" already exist" << endl;
			return false;
		}
		try
		{
			AddSolidBody(solidBodyType, solidBodyName);
			return true;
		}
		catch (const BodiesException& exception)
		{
			ExceptionHandler(exception);
			return false;
		}
	}
	if (bodyType == "compound")
	{
		string compoundBodyName;
		args >> compoundBodyName;
		if (CheckExistBody(compoundBodyName))
		{
			m_output << "Error: Bodies with name \"" << compoundBodyName << "\" already exist" << endl;
			return false;
		}
		try
		{
			AddCompoundBody(compoundBodyName);
			return true;
		}
		catch (const BodiesException& exception)
		{
			ExceptionHandler(exception);
			return false;
		}
	}
	m_output << "Error: unknown body type " << bodyType << endl;
	return false;
}

void BodiesContainer::AddCompoundBody(const string& name)
{
	m_nameToBodiesMap.emplace(name, make_shared<CCompound>());
}

void BodiesContainer::AddSolidBody(const string& type, const string& name)
{
	if (type == "sphere")
	{
		shared_ptr<CSphere> sphere = ReadSphereInfo();
		m_nameToBodiesMap.emplace(name, sphere);
		return;
	}
	if (type == "cone")
	{
		shared_ptr<CCone> cone = ReadConeInfo();
		m_nameToBodiesMap.emplace(name, cone);
		return;
	}
	if (type == "cylinder")
	{
		shared_ptr<CCylinder> cylinder = ReadCylinderInfo();
		m_nameToBodiesMap.emplace(name, cylinder);
		return;
	}
	if (type == "parallelepiped")
	{
		shared_ptr<CParallelepiped> parallelepiped = ReadParallelepipedInfo();
		m_nameToBodiesMap.emplace(name, parallelepiped);
		return;
	}
	throw BodiesException("unknown body type " + type);
}

shared_ptr<CSphere> BodiesContainer::ReadSphereInfo() const
{
	double radius = ReadParameter("Radius");
	double density = ReadParameter("Density");
	return make_shared<CSphere>(radius, density);
}

shared_ptr<CCone> BodiesContainer::ReadConeInfo() const
{
	double baseRadius = ReadParameter("Base radius");
	double height = ReadParameter("Height");
	double density = ReadParameter("Density");
	return make_shared<CCone>(baseRadius, height, density);
}

shared_ptr<CCylinder> BodiesContainer::ReadCylinderInfo() const
{
	double baseRadius = ReadParameter("Base radius");
	double height = ReadParameter("Height");
	double density = ReadParameter("Density");
	return make_shared<CCylinder>(baseRadius, height, density);
}

shared_ptr<CParallelepiped> BodiesContainer::ReadParallelepipedInfo() const
{
	double width = ReadParameter("Width");
	double height = ReadParameter("Height");
	double depth = ReadParameter("Depth");
	double density = ReadParameter("Density");
	return make_shared<CParallelepiped>(width, height, depth, density);
}

void BodiesContainer::PrintBodyWithBiggestMass() const
{
	string bodyWithMaxMassName;
	double maxMass = NAN;
	for (const auto& mapItem: m_nameToBodiesMap)
	{
		double mass = mapItem.second.get()->GetMass();
		if (isnan(maxMass) || mass > maxMass)
		{
			bodyWithMaxMassName = mapItem.first;
			maxMass = mass;
		}
	}
	m_output << m_nameToBodiesMap.at(bodyWithMaxMassName)->ToString() << endl;
}

double BodiesContainer::CalculateArhimedPowerInWater(shared_ptr<CBody> const& body) const
{
	return ACCELERATION_OF_GRAVITY * (body->GetMass() - ((body->GetDensity() - DENSITY_OF_WATER) * body->GetVolume()));
}
// разделить
void BodiesContainer::PrintBodyWithBiggestArhimedPower() const
{
	string bodyWithMaxArhimedPowerName;
	double maxArhimedPower = NAN;
	for (const auto& mapItem : m_nameToBodiesMap)
	{
		double arhimedPower = CalculateArhimedPowerInWater(mapItem.second);
		if (isnan(maxArhimedPower) || arhimedPower > maxArhimedPower)
		{
			bodyWithMaxArhimedPowerName = mapItem.first;
			maxArhimedPower = arhimedPower;
		}
	}
	m_output << m_nameToBodiesMap.at(bodyWithMaxArhimedPowerName)->ToString() << endl;
}

double BodiesContainer::ReadParameter(const string& parameterName) const
{
	string paramValue;
	m_output << parameterName << ": ";
	getline(m_input, paramValue);
	return stod(paramValue);
}

bool BodiesContainer::CheckExistBody(const string& name) const
{
	return m_nameToBodiesMap.find(name) != m_nameToBodiesMap.end();
}

shared_ptr<CBody> BodiesContainer::GetBodyByName(const std::string& name)
{
	return m_nameToBodiesMap.at(name);		
	throw "not found error";
}

void BodiesContainer::ExceptionHandler(BodiesException const& exception) const
{
	m_output << "Error: " << exception.GetMessage() << endl;
}

