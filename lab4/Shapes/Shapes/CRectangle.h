#include "Point.h"
#include "CSolidShape.h"

#pragma once

class CRectangle : public CSolidShape
{
public:
	CRectangle(Point topLeftPoint, double width, double height, uint32_t outlineColour, uint32_t fillColour);

	double GetArea() const override;
	double GetPerimeter() const override;

	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	void AppendProperties(std::ostream& strm) const override;

	Point m_topLeft;
	double m_width;
	double m_height;
};