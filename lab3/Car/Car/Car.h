#pragma once
#include <iostream>

enum class Direction
{
	FORWARD,
	STANDING_STILL,
	BACKWARD,
};

class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(int gear);
	bool SetSpeed(int speed);
	
	bool IsTurnedOn() const;

	Direction GetDirection() const;
	int GetGear() const;
	int GetSpeed() const;

private:
	void SetDirection();

	Direction m_direction = Direction::STANDING_STILL;

	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;
};
