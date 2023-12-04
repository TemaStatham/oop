#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& errorDescription)
	: std::invalid_argument(errorDescription)
{
}
