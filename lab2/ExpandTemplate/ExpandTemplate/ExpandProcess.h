#pragma once

#include "stdafx.h"

std::string ExpandTemplate(std::string const& tpl,
	std::map<std::string, std::string> const& params);

bool ExpandProcess(Arguments& args);

bool CheckValidPos(const std::vector<PositionUntouched>& positionsUntouched, size_t newPos);

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString,
	std::vector<PositionUntouched>& positionsUntouched);