#pragma once

class Car
{
public:
	Car();

	bool IsTurnedOn() const;

	int GetSpeed() const;

	int GetGear() const;

	bool TurnOnEngine();

	bool TurnOffEngine();

	bool SetGear(int gear);

	bool SetSpeed(int speed);


private:
	int m_turnedOn;
	int m_speed;
	int m_gear;

private:
	int ConvertUserSpeedInModel(int speed);
};

