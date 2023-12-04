#include "stdafx.h"
#include "task1.h"

int main()
{
	std::vector<double> numbers = ReadVector(std::cin);

	ProcessVector(numbers);

	PrintVector(numbers, std::cout);

	SortVector(numbers);

	PrintVector(numbers, std::cout);

    return 0;
}
