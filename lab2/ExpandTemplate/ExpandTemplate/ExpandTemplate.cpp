#include "ExpandProcess.h"
#include "ParseParams.h"
#include "stdafx.h"

int main(int argc, char* argv[])
{
	auto args = ParseParams(argc, argv);

	if (!args.has_value())
	{
		std::cout << "Error in command line arguments\n";
		return 1;
	}

	if (!ExpandProcess(args.value()))
	{
		std::cout << "Error expand process\n";
		return 1;
	}

	return 0;
}
