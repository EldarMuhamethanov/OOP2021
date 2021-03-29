#include <iostream>
#include "Car.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

const int GEAR_MAX = 5;
const int GEAR_MIN = -1;

void PrintErrorMessage(string msg)
{
	cout << msg << endl;
}

const map<int, vector<int>> GearToSpeedRangeMap{
	{-1, {0, 20}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}},
};

bool CheckSpeedInGear(int speed, int gear)
{
	vector<int> gearSpeedRange = GearToSpeedRangeMap.at(gear);
	return (speed >= gearSpeedRange[0] && speed <= gearSpeedRange[1]);
}

Direction GetDirectionBySpeedAndGear(int speed, int gear, Direction currDirection)
{
	if (gear > 0 && speed != 0)
	{
		return Direction::FORWARD;
	}
	if (gear == -1 && speed != 0)
	{
		return Direction::BACK;
	}
	if (speed == 0)
	{
		return Direction::STAY;
	}
	return currDirection;
}

Car::Car()
	: m_direction(Direction::STAY)
	, m_speed(0)
	, m_gear(0)
	, m_turnedOn(false)
{
}

Car::~Car()
{
}

Direction Car::GetDirection() const
{
	return m_direction;
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
	m_direction = Direction::STAY;
	m_speed = 0;
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear == 0 && m_direction == Direction::STAY)
	{
		m_turnedOn = false;
		return true;
	}
	PrintErrorMessage("Невозможно выключить двигатель, потому что машина в движении или передача не нейтральная");
	return false;
}

bool Car::SetGear(int gear)
{
	if (!m_turnedOn || gear < GEAR_MIN || gear > GEAR_MAX)
	{
		PrintErrorMessage("Двигатель не включен или введена некорректная передача");
		return false;
	}
	if (gear == m_gear)
	{
		return true;
	}
	if (gear == 0)
	{
		m_gear = gear;
		return true;
	}
	if ((m_direction == Direction::FORWARD && gear > 0)
		|| (m_direction == Direction::BACK && gear < 0))
	{
		if (CheckSpeedInGear(m_speed, gear))
		{
			m_gear = gear;
			return true;
		}
		PrintErrorMessage("На текущей скорости перключение на передачу " + to_string(gear) + " невозможно");
		return false;
	}
	else if (m_direction == Direction::STAY && (gear == -1 || gear == 1))
	{
		m_gear = gear;
		return true;
	}
	PrintErrorMessage("При данном направлении движения нельзя переключиться на передачу " + to_string(gear));
	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_turnedOn)
	{
		PrintErrorMessage("Нельзя изменить скорость с выключенным двигателем");
		return false;
	}

	speed = speed < 0 ? 0 : speed;

	if (speed == m_speed)
	{
		return true;
	}
	if (m_gear == 0)
	{
		if (m_speed > speed)
		{
			m_speed = speed;
			m_direction = GetDirectionBySpeedAndGear(speed, m_gear, m_direction);
			return true;
		}
		PrintErrorMessage("Нельзя увеличивать скорость на нейтральной передаче");
		return false;
	}

	if (CheckSpeedInGear(speed, m_gear))
	{
		m_direction = GetDirectionBySpeedAndGear(speed, m_gear, m_direction);
		m_speed = speed;
		return true;
	}
	PrintErrorMessage("На передаче " + to_string(m_gear) + " введенная скорость недопустима");
	return false;
}