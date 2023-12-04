#include "CShape.h"

CShape::CShape(std::string figureType, uint32_t outlineColour)
	: m_figureType(figureType)
	, m_outlineColour(outlineColour)
{
}

std::string CShape::GetFigureType() const
{
	return m_figureType;
}

uint32_t CShape::GetOutlineColour() const
{
	return m_outlineColour.value();
}

std::string CShape::ToString() const
{
	// цвет в понятном формате hex
	std::ostringstream strm;
	strm << m_figureType << ":" << std::endl
		 << std::setprecision(10)
		 << "\toutline colour = " << std::setfill('0') << std::hex << (m_outlineColour.has_value() ? m_outlineColour.value() : uint32_t(0000)) << std::endl
		 << "\tarea = " << GetArea() << std::endl
		 << "\tperimeter = " << GetPerimeter() << std::endl;
	AppendProperties(strm);
	return strm.str();
}
