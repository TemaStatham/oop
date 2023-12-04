#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

void URLWork(std::istream& in, std::ostream& out);
