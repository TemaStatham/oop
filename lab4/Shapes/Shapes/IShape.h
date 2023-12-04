#include <iomanip>
#include <iostream>
#include <sstream>

#pragma once

// #pragma warning(disable : 4250)

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual uint32_t GetOutlineColour() const = 0;
	virtual std::string ToString() const = 0;

	virtual std::string GetFigureType() const = 0;

	virtual ~IShape() = default;
};