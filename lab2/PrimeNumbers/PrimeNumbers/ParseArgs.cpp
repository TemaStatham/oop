#include "ParseArgs.h"

std::optional<int> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Didnt correct command stroke value\n";
		return std::nullopt;
	}

	int upperBound = std::atoi(argv[1]);
	if (upperBound > MAX_UPPER_BOUND || upperBound < MIN_PRIME_NUMBER)
	{
		std::cout << "Upper bound is didnt valid\n";
		return std::nullopt;
	}

	return upperBound;
}