#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../PrimeNumbers/EratosthenesSieve.h"
#include "../PrimeNumbers/ParseArgs.h"
#include <sstream>

SCENARIO("Check valid upper bound value")
{
	//слишком сложный тест
	WHEN("The value of upper bound is overflowing")
	{
		char arr1[] = { 'e', 'x', 'e', '\0' };
		char* exe = arr1;

		char arr2[] = { '1', '0', '0', '0', '0', '0', '0', '0', '1', '\0' };
		char* bound = arr2;

		char* argv[] = {
			{ exe },
			{ bound }
		};
		int argc = 2;

		auto upperBound = ParseArgs(argc, argv);
		REQUIRE(!upperBound.has_value());
	}

	WHEN("The value of upper bound is so small")
	{
		char arr1[] = { 'e', 'x', 'e', '\0' };
		char* exe = arr1;

		char arr2[] = { '1', '\0' };
		char* bound = arr2;

		char* argv[] = {
			{ exe },
			{ bound }
		};
		int argc = 2;

		auto upperBound = ParseArgs(argc, argv);
		REQUIRE(!upperBound.has_value());
	}
}

SCENARIO("Check work Eratosthenes Sieve algorithm")
{
	WHEN("Check work Eratosthenes Sieve algorithm")
	{
		int upperBound = MAX_UPPER_BOUND;
		std::set<int> set = GeneratePrimeNumbersSet(upperBound);
		REQUIRE(set.size() == 5761455);

		upperBound = 12;
		set = GeneratePrimeNumbersSet(upperBound);
		std::set<int> res = { 2, 3, 5, 7, 11 };
		REQUIRE(set == res);

		upperBound = 97;
		set = GeneratePrimeNumbersSet(upperBound);

		std::stringstream out;
		PrintSet(set, out);

		//
		REQUIRE(out.str() == "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 \n");

	}
}