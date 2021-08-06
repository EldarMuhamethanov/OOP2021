#pragma once
#include <vector>
#include <algorithm>

template<typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
		return false;
	size_t indexOfMax = 0;
	for (size_t i = 0; i < arr.size(); i++)
		if (less(maxValue, arr[i]))
			maxValue = arr[i];
	return true;
}