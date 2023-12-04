#include "FindMaxEx.h"

// template <typename T, typename Less>
// bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
//{
//	if (arr.empty())
//	{
//		return false;
//	}
//
//	auto maxIt = arr.begin();
//	for (auto it = arr.begin() + 1; it != arr.end(); ++it)
//	{
//		if (less(*maxIt, *it))
//		{
//			maxIt = it;
//		}
//	}
//	maxValue = *maxIt;
//
//	return true;
// }