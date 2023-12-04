#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/Car.h"
#include "../Car/CarControl.h"
#include <sstream>
// шоу тест ковераге
SCENARIO("Test Car")
{
	WHEN("Test engine on")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(!car.TurnOnEngine());
		REQUIRE(car.IsTurnedOn());
	}

	WHEN("Test car work")
	{
		Car car;
		WHEN("Test gear then engine off")
		{
			REQUIRE(!car.SetGear(5));
			REQUIRE(!car.SetGear(4));
			REQUIRE(!car.SetGear(3));
			REQUIRE(!car.SetGear(2));
			REQUIRE(!car.SetGear(1));
			REQUIRE(!car.SetGear(0));
			REQUIRE(!car.SetGear(-1));
			REQUIRE(!car.SetGear(6));
			REQUIRE(!car.SetGear(-2));
			WHEN("Test direction")
			{
				REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
			}
		}
		WHEN("Test speed then engine off")
		{
			REQUIRE(!car.SetSpeed(0));
			REQUIRE(!car.SetSpeed(20));
			REQUIRE(!car.SetSpeed(150));
			REQUIRE(!car.SetSpeed(-20));
			REQUIRE(!car.SetSpeed(-150));
			WHEN("Test direction")
			{
				REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
			}
		}
		car.TurnOnEngine();
		WHEN("Test gear -1")
		{
			REQUIRE(car.SetGear(-1));
			REQUIRE(car.GetGear() == -1);
			WHEN("Test speed for gear")
			{
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.GetSpeed() == 20);
				REQUIRE(!car.SetSpeed(-1));
				REQUIRE(car.GetSpeed() == 20);
				REQUIRE(!car.SetSpeed(21));
				REQUIRE(car.GetSpeed() == 20);
				WHEN("Test direction")
				{
					REQUIRE(car.GetDirection() == Direction::BACKWARD);
				}
			}
		}
		WHEN("Test gear 0")
		{
			REQUIRE(car.SetGear(0));
			REQUIRE(car.GetGear() == 0);
			WHEN("Test speed for gear")
			{
				REQUIRE(!car.SetSpeed(150));
				REQUIRE(car.GetSpeed() != 150);
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(!car.SetSpeed(-1));
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(!car.SetSpeed(151));
				REQUIRE(car.GetSpeed() == 0);
				car.SetGear(1);
				car.SetSpeed(20);
				REQUIRE(car.SetGear(0));
				REQUIRE(!car.SetSpeed(41));
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.GetSpeed() == 20);
				WHEN("Test direction")
				{
					REQUIRE(car.GetDirection() == Direction::FORWARD);
				}
				WHEN("Test gear 1")
				{
					REQUIRE(car.SetGear(1));
					REQUIRE(car.GetGear() == 1);
					WHEN("Test speed for gear")
					{
						REQUIRE(car.SetSpeed(0));
						REQUIRE(car.GetSpeed() == 0);
						REQUIRE(!car.SetSpeed(-1));
						REQUIRE(car.GetSpeed() == 0);
						REQUIRE(!car.SetSpeed(31));
						REQUIRE(car.GetSpeed() == 0);
						REQUIRE(car.SetSpeed(30));
						REQUIRE(car.GetSpeed() == 30);
						WHEN("Test direction")
						{
							REQUIRE(car.GetDirection() == Direction::FORWARD);
						}
						WHEN("Test gear 2")
						{
							REQUIRE(car.SetGear(2));
							REQUIRE(car.GetGear() == 2);
							WHEN("Test speed for gear")
							{
								REQUIRE(car.SetSpeed(20));
								REQUIRE(car.GetSpeed() == 20);
								REQUIRE(car.SetSpeed(50));
								REQUIRE(car.GetSpeed() == 50);
								REQUIRE(!car.SetSpeed(-1));
								REQUIRE(car.GetSpeed() == 50);
								REQUIRE(!car.SetSpeed(51));
								REQUIRE(car.GetSpeed() == 50);
								WHEN("Test direction")
								{
									REQUIRE(car.GetDirection() == Direction::FORWARD);
								}
								WHEN("Test gear 3")
								{
									REQUIRE(car.SetGear(3));
									REQUIRE(car.GetGear() == 3);
									WHEN("Test speed for gear")
									{
										REQUIRE(car.SetSpeed(30));
										REQUIRE(car.GetSpeed() == 30);
										REQUIRE(car.SetSpeed(60));
										REQUIRE(car.GetSpeed() == 60);
										REQUIRE(!car.SetSpeed(-1));
										REQUIRE(car.GetSpeed() == 60);
										REQUIRE(!car.SetSpeed(61));
										REQUIRE(car.GetSpeed() == 60);
										WHEN("Test direction")
										{
											REQUIRE(car.GetDirection() == Direction::FORWARD);
										}
										// почитать про фикстуры
										WHEN("Test gear 4")
										{
											REQUIRE(car.SetGear(4));
											REQUIRE(car.GetGear() == 4);
											WHEN("Test speed for gear")
											{
												REQUIRE(car.SetSpeed(40));
												REQUIRE(car.GetSpeed() == 40);
												REQUIRE(car.SetSpeed(90));
												REQUIRE(car.GetSpeed() == 90);
												REQUIRE(!car.SetSpeed(-1));
												REQUIRE(car.GetSpeed() == 90);
												REQUIRE(!car.SetSpeed(91));
												REQUIRE(car.GetSpeed() == 90);
												WHEN("Test direction")
												{
													REQUIRE(car.GetDirection() == Direction::FORWARD);
												}
												WHEN("Test gear 5")
												{
													REQUIRE(car.SetGear(5));
													REQUIRE(car.GetGear() == 5);
													WHEN("Test speed for gear")
													{
														REQUIRE(car.SetSpeed(50));
														REQUIRE(car.GetSpeed() == 50);
														REQUIRE(car.SetSpeed(150));
														REQUIRE(car.GetSpeed() == 150);
														REQUIRE(!car.SetSpeed(-1));
														REQUIRE(car.GetSpeed() == 150);
														REQUIRE(!car.SetSpeed(151));
														REQUIRE(car.GetSpeed() == 150);
														WHEN("Test direction")
														{
															REQUIRE(car.GetDirection() == Direction::FORWARD);
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		WHEN("Test engine off")
		{
			REQUIRE(car.TurnOffEngine());
			REQUIRE(!car.TurnOffEngine());
			REQUIRE(!car.IsTurnedOn());
		}
	}
}

SCENARIO("Test car control")
{
	WHEN("Test car control")
	{
		Car car;
		std::stringstream in("EngineOn\n"
							 "SetSpeed 20\n"
							 "SetSpeed 21\n"
							 "SetGear 3\n"
							 "SetSpeed 50\n"
							 "SetGear 0\n"
							 "SetSpeed 0\n"
							 "Exit\n");
		std::stringstream out;
		CarControl control(in, out, car);
		control.StartTrip();
		REQUIRE(out.str() == "Engine is on\n"
							 "Failed set speed to 20\n"
							 "Failed set speed to 21\n"
							 "Failed set gear to 3\n"
							 "Failed set speed to 50\n"
							 "Gear is 0\n"
							 "Speed is 0\n"
							 "Exit\n");
	}
	WHEN("Test car control")
	{
		Car car;
		std::stringstream in("EngineOn\n"
							 "SetGear -1\n"
							 "SetSpeed 20\n"
							 "SetGear 0\n"
							 "SetSpeed 21\n"
							 "SetSpeed 10\n"
							 "SetSpeed 0\n"
							 "SetGear 1\n"
							 "SetSpeed 20\n"
							 "SetGear 2\n"
							 "SetSpeed 40\n"
							 "SetGear 3\n"
							 "SetSpeed 60\n"
							 "SetGear 4\n"
							 "SetSpeed 90\n"
							 "SetGear 5\n"
							 "SetSpeed 150\n"
							 "SetGear 0\n"
							 "SetSpeed 0\n"
							 "EngineOff\n"
							 "Exit\n");
		std::stringstream out;
		CarControl control(in, out, car);
		control.StartTrip();
		REQUIRE(out.str() == "Engine is on\n"
							 "Gear is -1\n"
							 "Speed is 20\n"
							 "Gear is 0\n"
							 "Failed set speed to 21\n"
							 "Speed is 10\n"
							 "Speed is 0\n"
							 "Gear is 1\n"
							 "Speed is 20\n"
							 "Gear is 2\n"
							 "Speed is 40\n"
							 "Gear is 3\n"
							 "Speed is 60\n"
							 "Gear is 4\n"
							 "Speed is 90\n"
							 "Gear is 5\n"
							 "Speed is 150\n"
							 "Gear is 0\n"
							 "Speed is 0\n"
							 "Engine is off\n"
							 "Exit\n");
	}
	WHEN("Test print info")
	{
		Car car;
		std::stringstream in("EngineOn\n"
							 "SetGear 2\n"
							 "SetSpeed 50\n"
							 "PrintInfo\n"
							 "Exit\n");
		std::stringstream out;
		CarControl control(in, out, car);
		control.StartTrip();
		REQUIRE(out.str() == "Engine is on\n"
							 "Failed set gear to 2\n"
							 "Failed set speed to 50\n"
							 "Car engine is on\n"
							 "Car direction is standing still\n"
							 "Car gear is 0\n"
							 "Car speed is 0\n"
							 "Exit\n");
	}
}
