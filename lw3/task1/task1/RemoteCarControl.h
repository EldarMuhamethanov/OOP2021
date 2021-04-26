#pragma once
#include <iostream>
#include <map>
#include <functional>
#include "Car.h"
#include "CarException.h"

class RemoteCarControl
{
public:
	RemoteCarControl(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand() const;

private:
	bool EngineOn(std::istream& args) const;
	bool EngineOff(std::istream& args) const;
	bool Info(std::istream& args) const;
	bool SetSpeed(std::istream& args) const;
	bool SetGear(std::istream& args) const;
	void ExceptionHandler(CarException const& exception) const;
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};

