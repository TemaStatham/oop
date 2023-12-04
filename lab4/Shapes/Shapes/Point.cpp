#include "Point.h"
#include <cmath>

std::ostream& operator<<(std::ostream& stream, const Point& point)
{
	return stream << "{" << point.x << ", " << point.y << "}";
}

double GetDistance(const Point& left, const Point& right)
{
	return std::hypot(right.x - left.x, right.y - left.y);
}
