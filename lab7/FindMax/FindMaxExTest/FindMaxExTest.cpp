#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../FindMax/FindMaxEx.h"
#include <iostream>
#include <string>
#include <vector>

SCENARIO("Struct")
{
	struct Athlete
	{
		std::string name;
		double height;
		double weight;

		Athlete(const std::string& n, double h, double w)
			: name(n)
			, height(h)
			, weight(w)
		{
		}
	};

	struct HeightLess
	{
		bool operator()(const Athlete& a1, const Athlete& a2) const
		{
			return a1.height < a2.height;
		}
	};

	struct WeightLess
	{
		bool operator()(const Athlete& a1, const Athlete& a2) const
		{
			return a1.weight < a2.weight;
		}
	};

	std::vector<Athlete> athletes;

	athletes.push_back({ "Ivan", 10, 60 });
	athletes.push_back({ "Dmitriy", 20, 50 });
	athletes.push_back({ "Alexey", 30, 40 });
	athletes.push_back({ "Oleg", 40, 30 });
	athletes.push_back({ "Andrey", 50, 20 });
	athletes.push_back({ "kolya", 60, 10 });

	Athlete maxHighAthletes("", 0, 0);
	// ошибка
	if (FindMaxEx(athletes, maxHighAthletes, HeightLess()))
	{
		std::cout << "The highest sportsman '" << maxHighAthletes.name << "' with a height of: " << maxHighAthletes.height << std::endl;
	}

	Athlete maxWeightAthletes("", 0, 0);
	if (FindMaxEx(athletes, maxWeightAthletes, WeightLess()))
	{
		std::cout << "The heaviest sportsman '" << maxWeightAthletes.name << "' with a weight of: " << maxWeightAthletes.weight << std::endl;
	}
}

SCENARIO(" INT ")
{
	WHEN("Empty vector")
	{
		std::vector<int> empty;
		int maxValue;
		REQUIRE(FindMaxEx(empty, maxValue, [](int a, int b) { return a < b; }) == false);
	}

	WHEN("Vector of integers")
	{
		std::vector<int> numbers = { 1, 2, 3, 4, 5 };
		int maxValue;
		REQUIRE(FindMaxEx(numbers, maxValue, [](int a, int b) { return a < b; }));
		CHECK(maxValue == 5);
	}
}

SCENARIO("Double")
{
	WHEN("Empty vector")
	{
		std::vector<double> empty;
		double maxValue;
		REQUIRE(FindMaxEx(empty, maxValue, [](double a, double b) { return a < b; }) == false);
	}

	WHEN("Vector of integers")
	{
		std::vector<double> numbers = { 1.1, 1.2, 1.3, 1.4, 1.5 };
		double maxValue;
		REQUIRE(FindMaxEx(numbers, maxValue, [](double a, double b) { return a < b; }));
		CHECK(maxValue == 1.5);
	}
}

SCENARIO("String")
{
	WHEN("Empty vector")
	{
		std::vector<std::string> empty;
		std::string maxValue;
		REQUIRE(FindMaxEx(empty, maxValue, [](std::string a, std::string b) { return a < b; }) == false);
	}

	WHEN("Vector of integers")
	{
		std::vector<std::string> strings = { "abc", "abcd", "abcde" };
		std::string maxValue;
		REQUIRE(FindMaxEx(strings, maxValue, [](std::string a, std::string b) { return a < b; }));
		CHECK(maxValue == "abcde");
	}
}
