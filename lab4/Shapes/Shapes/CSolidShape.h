#pragma once
#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape
	: public ISolidShape
	, public CShape
{
public:
	CSolidShape(uint32_t fillColour, uint32_t outlineColour, const std::string& figureType);

	std::string ToString() const override;
	uint32_t GetOutlineColour() const override;
	std::string GetFigureType() const override;

	uint32_t GetFillColour() const override;
	void AppendFillColour(std::ostream& strm) const;

private:
	std::optional<uint32_t> m_fillColour;
};