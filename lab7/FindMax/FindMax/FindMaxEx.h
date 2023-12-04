#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto maxIt = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*maxIt, *it))
		{
			maxIt = it;
		}
	}
	// вы€снить что означает гаранти€ исключений
	maxValue = *maxIt;

	return true;
}