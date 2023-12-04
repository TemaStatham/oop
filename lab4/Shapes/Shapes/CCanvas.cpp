#include "CCanvas.h"

void CCanvas::DrawLine(Point from, Point to, uint32_t lineColour) const
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(from.x, from.y), sf::Color(lineColour)),
		sf::Vertex(sf::Vector2f(to.x, to.y), sf::Color(lineColour))
	};

	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(std::vector<Point> points, double lineColour, uint32_t colour) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}

	polygon.setFillColor(sf::Color(colour));
	polygon.setOutlineThickness(lineColour);
	polygon.setOutlineColor(sf::Color(lineColour));

	m_window.draw(polygon);
}

void CCanvas::DrawCircle(Point point, double radius, uint32_t lineColour) const
{
	sf::CircleShape circle(radius);
	circle.setPosition(point.x - radius, point.y - radius);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1);
	circle.setOutlineColor(sf::Color(lineColour));

	m_window.draw(circle);
}

void CCanvas::FillCircle(Point point, double radius, uint32_t fillColour) const
{
	sf::CircleShape circle(radius);
	circle.setPosition(point.x - radius, point.y - radius);
	circle.setFillColor(sf::Color(fillColour));
	circle.setOutlineThickness(0);

	m_window.draw(circle);
}

void CCanvas::DrawTriangle(Point vertex1, Point vertex2, Point vertex3, uint32_t lineColour) const
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(vertex1.x, vertex1.y), sf::Color(lineColour)),
		sf::Vertex(sf::Vector2f(vertex2.x, vertex2.y), sf::Color(lineColour)),
		sf::Vertex(sf::Vector2f(vertex3.x, vertex3.y), sf::Color(lineColour)),
		sf::Vertex(sf::Vector2f(vertex1.x, vertex1.y), sf::Color(lineColour))
	};

	m_window.draw(line, 4, sf::LinesStrip);
}

void CCanvas::FillTriangle(Point vertex1, Point vertex2, Point vertex3, uint32_t fillColour) const
{
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(vertex1.x, vertex1.y));
	triangle.setPoint(1, sf::Vector2f(vertex2.x, vertex2.y));
	triangle.setPoint(2, sf::Vector2f(vertex3.x, vertex3.y));
	triangle.setFillColor(sf::Color(fillColour));

	m_window.draw(triangle);
}

void CCanvas::DrawRectangle(Point topLeftPoint, double width, double height, uint32_t lineColour) const
{
	sf::RectangleShape rectangle(sf::Vector2f(width, height));
	rectangle.setPosition(topLeftPoint.x, topLeftPoint.y);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color(lineColour));

	m_window.draw(rectangle);
}

void CCanvas::FillRectangle(Point topLeftPoint, double width, double height, uint32_t fillColour) const
{
	sf::RectangleShape rectangle(sf::Vector2f(width, height));
	rectangle.setPosition(topLeftPoint.x, topLeftPoint.y);
	rectangle.setFillColor(sf::Color(fillColour));
	rectangle.setOutlineThickness(0);

	m_window.draw(rectangle);
}
