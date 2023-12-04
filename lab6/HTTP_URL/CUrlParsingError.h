#pragma once

#include "stdafx.h"

class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError(const std::string& errorDescription);
};