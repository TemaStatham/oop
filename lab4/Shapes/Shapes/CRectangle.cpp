#include "CRectangle.h"

CRectangle::CRectangle(Point topLeft, double width, double height, uint32_t outlineColour, uint32_t fillColour)
	: CSolidShape(fillColour, outlineColour, "rectangle")
	, m_topLeft(topLeft)
	, m_width(width)
	, m_height(height)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

Point CRectangle::GetLeftTop() const
{
	return m_topLeft;
}

Point CRectangle::GetRightBottom() const
{
	return { m_topLeft.x + m_width, m_topLeft.y - m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::AppendProperties(std::ostream& strm) const
{
	AppendFillColour(strm);
	strm << "\tleft top = " << m_topLeft << std::endl
		 << "\tright Bottom = " << GetRightBottom() << std::endl
		 << "\twidth = " << m_width << std::endl
		 << "\theight = " << m_height << std::endl;
}
