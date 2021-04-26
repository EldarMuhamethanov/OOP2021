#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Car.h"
#include "CarException.h"

using namespace std;

const int GEAR_MAX = 5;
const int GEAR_MIN = -1;

bool CheckSpeedInGear(int speed, int gear)
{
	static const map<int, vector<int>> GearToSpeedRangeMap{
		{-1, {-20, 0}},
		{1, {0, 30}},
		{2, {20, 50}},
		{3, {30, 60}},
		{4, {40, 90}},
		{5, {50, 150}},
	};
	vector<int> gearSpeedRange = GearToSpeedRangeMap.at(gear);
	return (speed >= gearSpeedRange[0] && speed <= gearSpeedRange[1]);
}

Car::Car()
	: m_speed(0)
	, m_gear(0)
	, m_turnedOn(false)
{
}

int Car::GetGear() const
{
	return m_gear;
}

int Car::GetSpeed() const
{
	return m_speed;
}

bool Car::IsTurnedOn() const
{
	return m_turnedOn;
}

bool Car::TurnOnEngine()
{
	m_gear = 0;
	m_turnedOn = true;
	m_speed = 0;
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_turnedOn = false;
		return true;
	}
	throw CarException("Невозможно выключить двигатель, потому что машина в движении или передача не нейтральная");
}

bool Car::SetGear(int gear)
{
	if (!m_turnedOn || gear < GEAR_MIN || gear > GEAR_MAX)
		throw CarException("Двигатель не включен или введена некорректная передача");

	if (gear == m_gear)
		return true;

	if (gear == 0)
	{
		m_gear = gear;
		return true;
	}
	if (m_gear == 0 && m_speed != 0)
		throw CarException("С нейтральной передачи нельзя переключиться на другую на ходу");

	if ((m_speed >= 0 && gear > 0) || (m_speed <= 0 && gear < 0))
	{
		if (CheckSpeedInGear(m_speed, gear))
		{
			m_gear = gear;
			return true;
		}
		throw CarException("На текущей скорости " + to_string(m_speed) + " на передачу " + to_string(gear) + " невозможно");
	}
	throw CarException("При данном направлении движения нельзя переключиться на передачу " + to_string(gear));
}

int Car::ConvertUserSpeedInModel(int userInputSpeed)
{
	userInputSpeed = userInputSpeed < 0 ? 0 : userInputSpeed;
	if (m_gear > 0)
		return userInputSpeed;
	if (m_gear < 0)
		return -userInputSpeed;
	return m_speed < 0 ? -userInputSpeed : userInputSpeed;
}

bool Car::SetSpeed(int speed)
{
	if (!m_turnedOn)
		throw CarException("Нельзя изменить скорость с выключенным двигателем");

	speed = ConvertUserSpeedInModel(speed);

	if (speed == m_speed)
		return true;

	if (m_gear == 0)
	{
		if (abs(m_speed) > abs(speed))
		{
			m_speed = speed;
			return true;
		}
		throw CarException("Нельзя увеличивать скорость на нейтральной передаче");
	}
	if (CheckSpeedInGear(speed, m_gear))
	{
		m_speed = speed;
		return true;
	}
	throw CarException("На передаче " + to_string(m_gear) + " введенная скорость недопустима");
}