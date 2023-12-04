#include "Car.h"
#include <map>

constexpr int MIN_GEAR = -1;
constexpr int MAX_GEAR = 5;
constexpr int NEUTRAL = 0;
constexpr int REVERSE = -1;

struct SpeedRange
{
	int minSpeed;
	int maxSpeed;
};

const std::map<int, SpeedRange> SPEED_RANGES = {
	{ REVERSE, { 0, 20 } },
	{ NEUTRAL, { 0, 150 } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } },
};

bool Car::TurnOnEngine()
{
	if (m_isEngineOn)
	{
		return false;
	}

	m_isEngineOn = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (!m_isEngineOn)
	{
		return false;
	}

	if (m_speed != 0 && m_gear != NEUTRAL)
	{
		return false;
	}

	m_isEngineOn = false;
	return true;
}

bool Car::SetGear(int gear)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	if (gear < MIN_GEAR || gear > MAX_GEAR)
	{
		return false;
	}

	if (m_direction == Direction::BACKWARD && gear > NEUTRAL)
	{
		return false;
	}

	if (m_direction == Direction::FORWARD && gear == REVERSE)
	{
		return false;
	}

	if ((m_gear > NEUTRAL && gear < NEUTRAL) && (m_gear < NEUTRAL && gear > NEUTRAL))
	{
		return false;
	}

	const SpeedRange range = SPEED_RANGES.at(gear);

	if (m_speed < range.minSpeed || m_speed > range.maxSpeed)
	{
		return false;
	}

	m_gear = gear;
	return true;
}

void Car::SetDirection()
{
	if (m_gear == MIN_GEAR && m_speed > 0)
	{
		m_direction = Direction::BACKWARD;
		return;
	}

	if (m_gear > NEUTRAL && m_speed > 0)
	{
		m_direction = Direction::FORWARD;
		return;
	}

	if (m_speed == 0)
	{
		m_direction = Direction::STANDING_STILL;
		return;
	}

	return;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	if (m_gear == NEUTRAL && speed > m_speed)
	{
		return false;
	}

	const SpeedRange range = SPEED_RANGES.at(m_gear);

	if (speed < range.minSpeed || speed > range.maxSpeed)
	{
		return false;
	}

	m_speed = speed;

	SetDirection();

	return true;
}

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
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
