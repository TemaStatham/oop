#pragma once

std::vector<double>ReadVector(std::istream& in);

void ProcessVector(std::vector<double>& numbers);

void PrintVector(std::vector<double>& numbers, std::ostream& out);

void SortVector(std::vector<double>& numbers);