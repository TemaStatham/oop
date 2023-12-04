#include "IShape.h"

#pragma once

// optional fill color and outline colour
class ISolidShape : virtual public IShape
{
public:
	virtual uint32_t GetFillColour() const = 0;
};
