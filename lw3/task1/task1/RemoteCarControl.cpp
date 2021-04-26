#include <string>
#include <sstream>
#include "RemoteCarControl.h"


using namespace std;
using namespace std::placeholders;

RemoteCarControl::RemoteCarControl(Car& car, istream& input, ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "EngineOn", bind(&RemoteCarControl::EngineOn, this, _1) },
		  { "EngineOff", bind(&RemoteCarControl::EngineOff, this, _1) },
		  { "Info", bind(&RemoteCarControl::Info, this, _1) },
		  { "SetSpeed", bind(&RemoteCarControl::SetSpeed, this, _1) },
		  { "SetGear", bind(&RemoteCarControl::SetGear, this, _1) },
		})
{
}

bool RemoteCarControl::HandleCommand() const
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
	m_output << "Неизвестная команда" << endl;
	return false;
}

bool RemoteCarControl::EngineOn(istream&) const
{
	m_car.TurnOnEngine();
	m_output << "Двигатель включен" << endl;
	return true;
}

bool RemoteCarControl::EngineOff(istream&) const
{
	try {
		m_car.TurnOffEngine();
		m_output << "Двигатель выключен" << endl;
		return true;
	}
	catch (CarException const& exception) {
		ExceptionHandler(exception);
		return false;
	}
}

string GetEngineState(bool IsTurnedOn)
{
	return IsTurnedOn ? "Включен" : "Выключен";
}

string GetDirectionState(int speed)
{
	if (speed > 0)
		return "Вперед";
	if (speed < 0)
		return "Назад";
	return "Стоит на месте";
}

bool RemoteCarControl::Info(istream&) const
{
	static const map<int, string> GearToDescriptionMap{
		{-1, "Задний ход"},
		{0, "Нейтральная"},
		{1, "Первая"},
		{2, "Вторая"},
		{3, "Третья"},
		{4, "Четвертая"},
		{5, "Пятая"},
	};

	bool isTurnedOn = m_car.IsTurnedOn();
	int gear = m_car.GetGear();
	int speed = m_car.GetSpeed();

	m_output << "Состояние двигателя: " << GetEngineState(isTurnedOn) << endl;
	m_output << "Включенная передача: " << GearToDescriptionMap.at(gear) << endl;
	m_output << "Текущая скорость: " << abs(speed) << endl;
	m_output << "Направление движения: " << GetDirectionState(speed) << endl;
	m_output << endl;

	return true;
}

bool RemoteCarControl::SetGear(istream& args) const
{
	int gear;
	args >> gear;
	try {
		m_car.SetGear(gear);
		m_output << "Передача сейчас " << gear << endl;
		return true;
	}
	catch (CarException const& exception) {
		ExceptionHandler(exception);
		return false;
	}
}

bool RemoteCarControl::SetSpeed(istream& args) const
{
	int speed;
	args >> speed;
	try {
		m_car.SetSpeed(speed);
		m_output << "Скорость сейчас " << speed << endl;
		return true;
	}
	catch (CarException const& exception) {
		ExceptionHandler(exception);
		return false;
	}
}

void RemoteCarControl::ExceptionHandler(CarException const& exception) const {
	m_output << "Ошибка: " << exception.GetMessage() << endl;
}