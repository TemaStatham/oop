#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <optional>

struct PositionUntouched
{
	size_t first, second;
};

struct Arguments
{
	std::string inputFileName, outputFileName;
	std::map<std::string, std::string> params;
};
