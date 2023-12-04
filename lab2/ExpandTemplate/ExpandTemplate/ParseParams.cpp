#include "ParseParams.h"

std::optional<Arguments> ParseParams(int argc, char* argv[])
{
	if (argc <= 2)
	{
		return std::nullopt;
	}

	std::map<std::string, std::string> params;

	for (size_t argumentsCount = 3; argumentsCount < argc; argumentsCount += 2)
	{
		if (argumentsCount + 1 >= argc)
		{
			break;
		}

		params.emplace(argv[argumentsCount + 1], argv[argumentsCount]);
	}

	Arguments args{ argv[1], argv[2], params };

	return args;
}
