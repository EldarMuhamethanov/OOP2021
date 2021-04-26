#pragma once
#include "CBody.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include "CCompound.h"
#include <iostream>
#include <functional>
#include <map>
#include <vector>

class BodiesContainer
{
public:
	BodiesContainer(std::istream& input, std::ostream& output);
	BodiesContainer(BodiesContainer const&) = delete;
	bool HandleCommand() const;

private:
	bool AddBody(std::istream& args);
	bool AppendBodyToCompoundBody(std::istream& args);
	bool Info(std::istream&);

	void PrintBodyWithBiggestMass() const;
	void PrintBodyWithBiggestArhimedPower() const;
	double CalculateArhimedPowerInWater(std::shared_ptr<CBody> const& body) const;

	void AddSolidBody(const std::string& type, const std::string& name);
	void AddCompoundBody(const std::string& name);

	std::shared_ptr<CSphere> ReadSphereInfo() const;
	std::shared_ptr<CCone> ReadConeInfo() const;
	std::shared_ptr<CCylinder> ReadCylinderInfo() const;
	std::shared_ptr<CParallelepiped> ReadParallelepipedInfo() const;

	double ReadParameter(const std::string& parameterName) const;
	bool CheckExistBody(const std::string& name) const;

	void ExceptionHandler(BodiesException const& exception) const;

	std::shared_ptr<CBody> GetBodyByName(const std::string& name);
private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
	std::map<std::string, std::shared_ptr<CBody>> m_nameToBodiesMap;
};

