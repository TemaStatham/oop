#include "Point.h"
#include "CSolidShape.h"

#pragma once

class CTriangle : public CSolidShape
{
public:
	CTriangle(
		const Point& firstPoint,
		const Point& secondPoint,
		const Point& thirdPoint,
		uint32_t outlineColour,
		uint32_t fillColour);

	double GetArea() const override;
	double GetPerimeter() const override;

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	void AppendProperties(std::ostream& strm) const override;

	Point m_firstPoint;
	Point m_secondPoint;
	Point m_thirdPoint;
};