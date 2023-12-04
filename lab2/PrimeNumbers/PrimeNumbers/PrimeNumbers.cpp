#include "EratosthenesSieve.h"
#include "ParseArgs.h"

int main(int argc, char* argv[])
{
	auto upperBound = ParseArgs(argc, argv);
	
	if (!upperBound.has_value())
	{
		return 1;
	}

	std::set<int> set = GeneratePrimeNumbersSet(upperBound.value());
	
	PrintSet(set, std::cout);

	return 0;
}
