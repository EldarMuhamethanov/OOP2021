#pragma once

enum class Direction {
	FORWARD,
	BACK,
	STAY,
};

class Car
{
public:
	Car();

	~Car();

	bool IsTurnedOn() const;

	Direction GetDirection() const;

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
	Direction m_direction;
};

