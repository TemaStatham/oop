#include "CShape.h"
#include "Point.h"

#pragma once

class CLineSegment : public CShape
{
public:
	CLineSegment(Point startPoint, Point endPoint, uint32_t outlineColour);

	double GetArea() const override;
	double GetPerimeter() const override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	void AppendProperties(std::ostream& strm) const override;

	Point m_startPoint;
	Point m_endPoint;
};