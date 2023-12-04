#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <cmath>

constexpr int MAX_UPPER_BOUND = 100000000, MIN_PRIME_NUMBER = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSet(std::set<int>& set, std::ostream& out);
