#include "ICanvas.h"
#include <SFML/Graphics.hpp>
#pragma once

class CCanvas : public ICanvas
{
public:
	CCanvas() = default;

	void DrawLine(Point from, Point to, uint32_t lineColour) const override;
	void FillPolygon(std::vector<Point> points, double lineColour, uint32_t colour) const override;

	void DrawCircle(Point point, double radius, uint32_t lineColour) const override;
	void FillCircle(Point point, double radius, uint32_t fillColour) const override;

	void DrawTriangle(Point vertex1, Point vertex2, Point vertex3, uint32_t lineColour) const override;
	void FillTriangle(Point vertex1, Point vertex2, Point vertex3, uint32_t fillColout) const override;

	void DrawRectangle(Point topLeftPoint, double width, double height, uint32_t lineColour) const override;
	void FillRectangle(Point topLeftPoint, double width, double height, uint32_t fillColour) const override;

private:
	sf::RenderWindow& m_window;
};