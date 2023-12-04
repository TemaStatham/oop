#include "Point.h"
#include <vector>

#pragma once

class ICanvas
{
public:
	virtual void DrawLine(Point from, Point to, uint32_t lineColour) const = 0;
	virtual void FillPolygon(std::vector<Point> points, double lineColour, uint32_t colour) const = 0;

	virtual void DrawCircle(Point point, double radius, uint32_t lineColour) const = 0;
	virtual void FillCircle(Point point, double radius, uint32_t fillColour) const = 0;

	virtual void DrawTriangle(Point vertex1, Point vertex2, Point vertex3, uint32_t lineColour) const = 0;
	virtual void FillTriangle(Point vertex1, Point vertex2, Point vertex3, uint32_t fillColout) const = 0;

	virtual void DrawRectangle(Point topLeftPoint, double width, double height, uint32_t lineColour) const = 0;
	virtual void FillRectangle(Point topLeftPoint, double width, double height, uint32_t fillColour) const = 0;

	virtual ~ICanvas() = default;
};