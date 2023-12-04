#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../VectorProcessing/task1.h"
#include <sstream>

SCENARIO("Сheck that the numbers are correctly read into the vector")
{
	WHEN("Сheck that a blank line is correctly read")
	{
		std::stringstream in("");
		auto vector = ReadVector(in);

		REQUIRE(vector.empty());
	}

	WHEN("Сheck to read the numbers")
	{
		std::stringstream in("1 2 3 4");
		auto vector = ReadVector(in);

		std::vector<double>res{ 1, 2, 3, 4 };
		
		REQUIRE(vector == res);
	}

	WHEN("Сheck to read the not numbers")
	{
		std::stringstream in("1 2 c 4");
		auto vector = ReadVector(in);

		REQUIRE(vector == std::vector<double>());
	}
}

SCENARIO("Check that the software is working correctly")
{
	WHEN("If an empty vector is entered, it will remain empty and its length will be 0")
	{
		std::vector<double>numbers;
		ProcessVector(numbers);

		REQUIRE(numbers.size() == 0);
		REQUIRE(numbers == std::vector<double>());
	}

	WHEN("Сhecking calculations of positive numbers")
	{
		std::vector<double>numbers{1, 2, 3, 4};
		ProcessVector(numbers);

		std::vector<double>res{3.5, 4.5, 5.5, 6.5};

		REQUIRE(numbers.size() == 4);
		REQUIRE(numbers == res);
	}

	WHEN("Сhecking calculations of different numbers")
	{
		std::vector<double>numbers{ -1, 2, 3, 4 };
		ProcessVector(numbers);

		std::vector<double>res{ 2, 5, 6, 7 };

		REQUIRE(numbers.size() == 4);
		REQUIRE(numbers == res);
	}

	WHEN("Сheck calculations for negative numbers")
	{
		std::vector<double>numbers{ -1, -2, -3, -4 };
		ProcessVector(numbers);

		std::vector<double>res{ -1, -2, -3, -4 };

		REQUIRE(numbers.size() == 4);
		REQUIRE(numbers == res);
	}
}

SCENARIO("Print check")
{
	WHEN("Сheck the output of an empty vector")
	{
		std::stringstream out;
		std::vector<double>vec;
		
		PrintVector(vec, out);
		REQUIRE(out.str() == "\n");
	}

	WHEN("Сheck the output of an vector")
	{
		std::stringstream out;
		std::vector<double>vec{1, 2, 3, 4};

		PrintVector(vec, out);
		REQUIRE(out.str() == "1 2 3 4 \n");
	}
}

SCENARIO("Check sort vector")
{
	WHEN("Сheck sort vector")
	{
		std::vector<double>vec{ 4, 3, 2, 1 };

		SortVector(vec);

		std::vector<double> res{ 1, 2, 3, 4 };

		REQUIRE(vec == res);
	}
}