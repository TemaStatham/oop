#include "Point.h"
#include "CSolidShape.h"
#include <iostream>

#pragma once

class CCircle : public CSolidShape
{
public:
	CCircle(Point center, double radius, uint32_t outlineColour, uint32_t fillColour);

	double GetArea() const override;
	double GetPerimeter() const override;

	Point GetCenter() const;
	double GetRadius() const;

private:
	void AppendProperties(std::ostream& strm) const override;

	Point m_center;
	double m_radius;
};