#include "CSolidShape.h"

CSolidShape::CSolidShape(uint32_t fillColour, uint32_t outlineColour, const std::string& figureType)
	: CShape(figureType, outlineColour)
	, m_fillColour(fillColour)
{
}

std::string CSolidShape::ToString() const
{
	return CShape::ToString();
}

uint32_t CSolidShape::GetOutlineColour() const
{
	return CShape::GetOutlineColour();
}

std::string CSolidShape::GetFigureType() const
{
	return CShape::GetFigureType();
}

uint32_t CSolidShape::GetFillColour() const
{
	return m_fillColour.value();
}

void CSolidShape::AppendFillColour(std::ostream& strm) const
{
	strm << "\tfill colour = " << (m_fillColour.has_value() ? m_fillColour.value() : uint32_t(000)) << std::endl;
}
