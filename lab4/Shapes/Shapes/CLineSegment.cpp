#include "CLineSegment.h"

CLineSegment::CLineSegment(Point startPoint, Point endPoint, uint32_t outlineColour)
	: CShape("line", outlineColour)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return GetDistance(m_startPoint, m_endPoint);
}

Point CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::AppendProperties(std::ostream& strm) const
{
	strm << "\tstart point = " << m_startPoint << std::endl
		 << "\tend point = " << m_endPoint << std::endl;
}
