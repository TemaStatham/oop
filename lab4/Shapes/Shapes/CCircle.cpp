#include "CCircle.h"
#define _USE_MATH_DEFINES
#include <math.h>

CCircle::CCircle(Point center, double radius, uint32_t outlineColour, uint32_t fillColour)
	: CSolidShape(fillColour, outlineColour, "circle")
	, m_center(center)
	, m_radius(radius)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

Point CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::AppendProperties(std::ostream& strm) const
{
	AppendFillColour(strm);
	strm << "\tcenter = " << m_center << std::endl
		 << "\tradius = " << m_radius << std::endl;
}
