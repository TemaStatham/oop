#include <iostream>
#pragma once

std::ostream& operator<<(std::ostream& stream, const Point& point);

double GetDistance(const Point& left, const Point& right);

struct Point
{
	double x;
	double y;
};
