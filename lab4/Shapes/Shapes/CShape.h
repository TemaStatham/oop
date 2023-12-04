#include "IShape.h"
#include <optional>

#pragma once

class CShape : virtual public IShape
{
public:
	CShape(std::string figureType, uint32_t outlineColour);

	std::string ToString() const override;
	uint32_t GetOutlineColour() const override;

	std::string GetFigureType() const override;

	virtual ~CShape() = default;

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;

	std::string m_figureType;
	std::optional<uint32_t> m_outlineColour;
};
