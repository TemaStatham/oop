#pragma once
#include "Car.h"
#include <map>

class CarControl
{
public:
	CarControl(std::istream& input, std::ostream& output, Car& car);
	void StartTrip();

private:
	enum class Command
	{
		PRINT_INFO,
		ENGINE_ON,
		ENGINE_OFF,
		SET_GEAR,
		SET_SPEED,
		EXIT,
	};

	const std::map<std::string, Command> Commands{
		{ "printinfo", Command::PRINT_INFO },
		{ "engineon", Command::ENGINE_ON },
		{ "engineoff", Command::ENGINE_OFF },
		{ "setgear", Command::SET_GEAR },
		{ "setspeed", Command::SET_SPEED },
		{ "exit", Command::EXIT },
	};

	struct Instruction
	{
		Command command;
		int argument;
	};

	Command ParseCommand(const std::string& commandStr);

	std::istream& m_in;
	std::ostream& m_out;
	Car& m_car;

	Command GetInstruction();
	void PrintInfo();
	void EngineOn();
	void EngineOff();
	void SetGear();
	void SetSpeed();
};
