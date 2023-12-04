#include "CTriangle.h"

CTriangle::CTriangle(
	const Point& firstPoint,
	const Point& secondPoint,
	const Point& thirdPoint,
	uint32_t outlineColour, uint32_t fillColour)
	: CSolidShape(fillColour, outlineColour, "triangle")
	, m_firstPoint(firstPoint)
	, m_secondPoint(secondPoint)
	, m_thirdPoint(thirdPoint)
{
}

double CTriangle::GetArea() const
{
	double a = GetDistance(m_firstPoint, m_secondPoint);
	double b = GetDistance(m_secondPoint, m_thirdPoint);
	double c = GetDistance(m_thirdPoint, m_firstPoint);
	double p = 0.5 * (a + b + c);

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	double a = GetDistance(m_firstPoint, m_secondPoint);
	double b = GetDistance(m_secondPoint, m_thirdPoint);
	double c = GetDistance(m_thirdPoint, m_firstPoint);

	return a + b + c;
}

Point CTriangle::GetVertex1() const
{
	return m_firstPoint;
}

Point CTriangle::GetVertex2() const
{
	return m_secondPoint;
}

Point CTriangle::GetVertex3() const
{
	return m_thirdPoint;
}

void CTriangle::AppendProperties(std::ostream& strm) const
{
	AppendFillColour(strm);
	strm << "\tvertex 1 = " << m_firstPoint << std::endl
		 << "\tvertex 2 = " << m_secondPoint << std::endl
		 << "\tvertex 3 = " << m_thirdPoint << std::endl;
}
