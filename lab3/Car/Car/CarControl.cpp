#include "CarControl.h"
#include "signal.h"
#include <sstream>
#include <string>

constexpr int INIT_ARGUMNET = 0;

std::string TransformStringToLowerCase(const std::string& str)
{
	std::string res;
	for (char ch : str)
	{
		res += std::tolower(static_cast<unsigned char>(ch));
	}
	return res;
}

std::string TransferDirectionToString(Direction direction)
{
	switch (direction)
	{
	case Direction::FORWARD:
		return "forward";
	case Direction::STANDING_STILL:
		return "standing still";
	case Direction::BACKWARD:
		return "backward";
	}
	return "standing still";
}

void SignalHandler(int signum)
{
	exit(signum);
}

CarControl::CarControl(std::istream& input, std::ostream& output, Car& car)
	: m_in(input)
	, m_out(output)
	, m_car(car){};

CarControl::Command CarControl::ParseCommand(const std::string& commandStr)
{
	std::string comandInLowerCase = TransformStringToLowerCase(commandStr);

	auto it = CarControl::Commands.find(commandStr);
	if (it != CarControl::Commands.end())
	{
		return it->second;
	}

	m_out << "I dont know this command" << std::endl;
	return CarControl::Command::EXIT;
}

CarControl::Command CarControl::GetInstruction()
{
	std::string instructionStr;

	signal(SIGINT, SignalHandler);

	if (!(m_in >> instructionStr))
	{
		m_out << "Failed to read instruction" << std::endl;
		return CarControl::Command::EXIT;
	}

	return ParseCommand(instructionStr);
}

void CarControl::PrintInfo()
{
	m_out << "Car engine is " << (m_car.IsTurnedOn() ? "on" : "off") << std::endl
		  << "Car direction is " << TransferDirectionToString(m_car.GetDirection()) << std::endl
		  << "Car gear is " << m_car.GetGear() << std::endl
		  << "Car speed is " << m_car.GetSpeed() << std::endl;
}

void CarControl::EngineOn()
{
	if (m_car.TurnOnEngine())
	{
		m_out << "Engine is on" << std::endl;
		return;
	}
	m_out << "Failed to turn on the engine" << std::endl;
}

void CarControl::EngineOff()
{
	if (m_car.TurnOffEngine())
	{
		m_out << "Engine is off" << std::endl;
		return;
	}
	m_out << "Failed to turn off the engine" << std::endl;
}

void CarControl::SetGear()
{
	int gear = INIT_ARGUMNET;
	if (!(m_in >> gear))
	{
		m_out << "Failed set gear to " << gear << std::endl;
		return;
	}
	if (m_car.SetGear(gear))
	{
		m_out << "Gear is " << gear << std::endl;
		return;
	}
	m_out << "Failed set gear to " << gear << std::endl;
}

void CarControl::SetSpeed()
{
	int speed = INIT_ARGUMNET;
	if (!(m_in >> speed))
	{
		m_out << "Failed set speed to " << speed << std::endl;
		return;
	}
	if (m_car.SetSpeed(speed))
	{
		m_out << "Speed is " << speed << std::endl;
		return;
	}
	m_out << "Failed set speed to " << speed << std::endl;
}

void CarControl::StartTrip()
{
	while (true)
	{
		const auto instruction = GetInstruction();

		switch (instruction)
		{
		case Command::PRINT_INFO:
			PrintInfo();
			break;
		case Command::ENGINE_ON:
			EngineOn();
			break;
		case Command::ENGINE_OFF:
			EngineOff();
			break;
		case Command::SET_GEAR:
			SetGear();
			break;
		case Command::SET_SPEED:
			SetSpeed();
			break;
		case Command::EXIT:
			m_out << "Exit" << std::endl;
			return;
		default:
			continue;
		}
	}
}
