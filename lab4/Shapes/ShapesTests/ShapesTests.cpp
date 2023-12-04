#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Shapes/CCircle.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/IShape.h"
#include "../Shapes/ISolidShape.h"
#include "../Shapes/Point.h"
#include "../Shapes/ShapeController.h"
#define _USE_MATH_DEFINES
#include <limits.h>
#include <math.h>

SCENARIO("Test class IShape")
{
	WHEN("Test with class CCircle")
	{
		constexpr double x = 1, y = 1, r = 5;
		const uint32_t outlineColour = 10, fillColour = 10;

		IShape* circle = new CCircle({ x, y }, r, outlineColour, fillColour);

		REQUIRE(circle->GetArea() == Approx(78.5398163397));
		REQUIRE(circle->GetOutlineColour() == outlineColour);
		REQUIRE(circle->GetPerimeter() == Approx(31.4159265359));
		REQUIRE(circle->GetFigureType() == "circle");
	}

	WHEN("Test with class CCircle : overflow")
	{
		constexpr double x = std::numeric_limits<double>::max(), y = std::numeric_limits<double>::max(), r = std::numeric_limits<double>::max();
		const uint32_t outlineColour = UINT32_MAX, fillColour = UINT32_MAX;

		IShape* circle = new CCircle({ x, y }, r, outlineColour, fillColour);

		REQUIRE(isinf(circle->GetArea()));
		REQUIRE(circle->GetOutlineColour() == outlineColour);
		REQUIRE(isinf(circle->GetPerimeter()));
		REQUIRE(circle->GetFigureType() == "circle");
	}

	WHEN("Test with class CLineSegment")
	{
		constexpr double x1 = 1, y1 = 1, x2 = -1, y2 = -1;
		const uint32_t outlineColour = 5;

		IShape* line = new CLineSegment({ x1, y1 }, { x2, y2 }, outlineColour);

		REQUIRE(line->GetArea() == Approx(0));
		REQUIRE(line->GetOutlineColour() == outlineColour);
		REQUIRE(line->GetPerimeter() == Approx(2.8284271247));
		REQUIRE(line->GetFigureType() == "line");
	}

	WHEN("Test with class CLineSegment : overflow")
	{
		constexpr double x1 = std::numeric_limits<double>::max(),
						 y1 = std::numeric_limits<double>::max(),
						 x2 = std::numeric_limits<double>::min(),
						 y2 = std::numeric_limits<double>::min();
		const uint32_t outlineColour = UINT32_MAX;

		IShape* line = new CLineSegment({ x1, y1 }, { x2, y2 }, outlineColour);

		REQUIRE(line->GetArea() == Approx(0));
		REQUIRE(line->GetOutlineColour() == outlineColour);
		REQUIRE(isinf(line->GetPerimeter()));
		REQUIRE(line->GetFigureType() == "line");
	}

	WHEN("Test with class CRectangle")
	{
		constexpr double x = 10, y = 10, width = 100, height = 30;
		const uint32_t outlineColour = 100, fillColour = 5;

		IShape* rectangle = new CRectangle({ x, y }, width, height, outlineColour, fillColour);

		REQUIRE(rectangle->GetArea() == Approx(3000.0));
		REQUIRE(rectangle->GetOutlineColour() == outlineColour);
		REQUIRE(rectangle->GetPerimeter() == Approx(260.0));
		REQUIRE(rectangle->GetFigureType() == "rectangle");
	}

	WHEN("Test with class CRectangle : overflow")
	{
		constexpr double
			x
			= std::numeric_limits<double>::max(),
			y = std::numeric_limits<double>::max(),
			width = std::numeric_limits<double>::max(), height = std::numeric_limits<double>::max();
		const uint32_t outlineColour = UINT32_MAX, fillColour = UINT32_MAX;

		IShape* rectangle = new CRectangle({ x, y }, width, height, outlineColour, fillColour);

		REQUIRE(isinf(rectangle->GetArea()));
		REQUIRE(rectangle->GetOutlineColour() == outlineColour);
		REQUIRE(isinf(rectangle->GetPerimeter()));
		REQUIRE(rectangle->GetFigureType() == "rectangle");
	}

	WHEN("Test with class CTriangle")
	{
		constexpr double x1 = 1, y1 = 1,
						 x2 = 100, y2 = 10,
						 x3 = 4, y3 = 4;
		const uint32_t outlineColour = 115, fillColour = 25;

		IShape* triangle = new CTriangle({ x1, y1 }, { x2, y2 }, { x3, y3 }, outlineColour, fillColour);

		REQUIRE(triangle->GetArea() == Approx(135.0));
		REQUIRE(triangle->GetOutlineColour() == outlineColour);
		REQUIRE(triangle->GetFigureType() == "triangle");
		REQUIRE(triangle->GetPerimeter() == Approx(199.8382070931));
	}

	WHEN("Test with class CTriangle : overflow")
	{
		constexpr double
			x1
			= std::numeric_limits<double>::max(),
			y1 = std::numeric_limits<double>::max(),
			x2 = std::numeric_limits<double>::max(), y2 = std::numeric_limits<double>::min(),
			x3 = std::numeric_limits<double>::min(), y3 = std::numeric_limits<double>::min();
		const uint32_t outlineColour = UINT32_MAX, fillColour = UINT32_MAX;

		IShape* triangle = new CTriangle({ x1, y1 }, { x2, y2 }, { x3, y3 }, outlineColour, fillColour);

		REQUIRE(isnan(triangle->GetArea()));
		REQUIRE(triangle->GetOutlineColour() == outlineColour);
		REQUIRE(triangle->GetFigureType() == "triangle");
		REQUIRE(isinf(triangle->GetPerimeter()));
	}
}

SCENARIO("Test class CCircle")
{
	constexpr double x = 1, y = 1, r = 5;
	const uint32_t outlineColour = 10, fillColour = 10;

	CCircle circle({ x, y }, r, outlineColour, fillColour);

	REQUIRE(circle.GetArea() == Approx(78.5398163397));
	REQUIRE(circle.GetOutlineColour() == outlineColour);
	REQUIRE(circle.GetPerimeter() == Approx(31.4159265359));
	REQUIRE(circle.GetFillColour() == fillColour);
	REQUIRE(circle.GetFigureType() == "circle");

	Point center = circle.GetCenter();

	REQUIRE(center.x == Approx(1));
	REQUIRE(center.y == Approx(1));

	REQUIRE(circle.GetRadius() == Approx(5));

	REQUIRE(circle.GetFillColour() == fillColour);
}

SCENARIO("Test with class CCircle : overflow")
{
	constexpr double x = std::numeric_limits<double>::max(), y = std::numeric_limits<double>::max(), r = std::numeric_limits<double>::max();
	const uint32_t outlineColour = UINT32_MAX, fillColour = UINT32_MAX;

	CCircle circle({ x, y }, r, outlineColour, fillColour);

	REQUIRE(isinf(circle.GetArea()));
	REQUIRE(circle.GetOutlineColour() == outlineColour);
	REQUIRE(isinf(circle.GetPerimeter()));
	REQUIRE(circle.GetFigureType() == "circle");

	Point center = circle.GetCenter();

	REQUIRE(center.x == Approx(std::numeric_limits<double>::max()));
	REQUIRE(center.y == Approx(std::numeric_limits<double>::max()));

	REQUIRE(circle.GetRadius() == Approx(std::numeric_limits<double>::max()));

	REQUIRE(circle.GetFillColour() == fillColour);
}

SCENARIO("Test class CLineSegment")
{
	constexpr double x1 = 1, y1 = 1, x2 = -1, y2 = -1;
	const uint32_t outlineColor = 5;

	CLineSegment line({ x1, y1 }, { x2, y2 }, outlineColor);

	REQUIRE(line.GetArea() == Approx(0));
	REQUIRE(line.GetOutlineColour() == outlineColor);
	REQUIRE(line.GetPerimeter() == Approx(2.8284271247));
	REQUIRE(line.GetFigureType() == "line");

	Point p1 = line.GetStartPoint(), p2 = line.GetEndPoint();

	REQUIRE(p1.x == Approx(1));
	REQUIRE(p1.y == Approx(1));
	REQUIRE(p2.x == Approx(-1));
	REQUIRE(p2.y == Approx(-1));
}

SCENARIO("Test class CLineSegment : overflow")
{
	constexpr double
		x1
		= std::numeric_limits<double>::max(),
		y1 = std::numeric_limits<double>::max(),
		x2 = std::numeric_limits<double>::min(), y2 = std::numeric_limits<double>::min();
	const uint32_t outlineColor = 5;

	CLineSegment line({ x1, y1 }, { x2, y2 }, outlineColor);

	REQUIRE(line.GetArea() == Approx(0));
	REQUIRE(line.GetOutlineColour() == outlineColor);
	REQUIRE(isinf(line.GetPerimeter()));
	REQUIRE(line.GetFigureType() == "line");

	Point p1 = line.GetStartPoint(), p2 = line.GetEndPoint();

	REQUIRE(p1.x == Approx(std::numeric_limits<double>::max()));
	REQUIRE(p1.y == Approx(std::numeric_limits<double>::max()));
	REQUIRE(p2.x == Approx(std::numeric_limits<double>::min()));
	REQUIRE(p2.y == Approx(std::numeric_limits<double>::min()));
}

SCENARIO("Test class CRectangle")
{
	constexpr double x = 10, y = 10, width = 100, height = 30;
	const uint32_t outlineColour = 100, fillColour = 5;

	CRectangle rectangle({ x, y }, width, height, outlineColour, fillColour);

	REQUIRE(rectangle.GetArea() == Approx(3000.0));
	REQUIRE(rectangle.GetOutlineColour() == outlineColour);
	REQUIRE(rectangle.GetPerimeter() == Approx(260.0));
	REQUIRE(rectangle.GetFigureType() == "rectangle");

	Point left = rectangle.GetLeftTop(), right = rectangle.GetRightBottom();

	REQUIRE(left.x == Approx(10));
	REQUIRE(left.y == Approx(10));
	REQUIRE(right.x == Approx(110));
	REQUIRE(right.y == Approx(-20));

	REQUIRE(rectangle.GetHeight() == Approx(30));
	REQUIRE(rectangle.GetWidth() == Approx(100));

	REQUIRE(rectangle.GetFillColour() == fillColour);
}

SCENARIO("Test with class CRectangle : overflow")
{
	constexpr double
		x
		= std::numeric_limits<double>::max(),
		y = std::numeric_limits<double>::max(),
		width = std::numeric_limits<double>::max(), height = std::numeric_limits<double>::max();
	const uint32_t outlineColour = UINT32_MAX, fillColour = UINT32_MAX;

	CRectangle rectangle({ x, y }, width, height, outlineColour, fillColour);

	REQUIRE(isinf(rectangle.GetArea()));
	REQUIRE(rectangle.GetOutlineColour() == outlineColour);
	REQUIRE(isinf(rectangle.GetPerimeter()));
	REQUIRE(rectangle.GetFigureType() == "rectangle");

	Point left = rectangle.GetLeftTop(), right = rectangle.GetRightBottom();

	REQUIRE(left.x == Approx(std::numeric_limits<double>::max()));
	REQUIRE(left.y == Approx(std::numeric_limits<double>::max()));
	REQUIRE(right.x == Approx(std::numeric_limits<double>::max()));
	REQUIRE(right.x == Approx(std::numeric_limits<double>::max()));

	REQUIRE(rectangle.GetHeight() == Approx(std::numeric_limits<double>::max()));
	REQUIRE(rectangle.GetWidth() == Approx(std::numeric_limits<double>::max()));

	REQUIRE(rectangle.GetFillColour() == fillColour);
}

SCENARIO("Test class CTriangle")
{
	constexpr double x1 = 1, y1 = 1,
					 x2 = 10, y2 = 10,
					 x3 = 4, y3 = 5;
	const uint32_t outlineColour = 115, fillColour = 25;

	CTriangle triangle({ x1, y1 }, { x2, y2 }, { x3, y3 }, outlineColour, fillColour);

	REQUIRE(triangle.GetArea() == Approx(4.5));
	REQUIRE(triangle.GetOutlineColour() == outlineColour);
	REQUIRE(triangle.GetFigureType() == "triangle");
	REQUIRE(triangle.GetPerimeter() == Approx(25.5381717373));

	Point ver1 = triangle.GetVertex1(), ver2 = triangle.GetVertex2(), ver3 = triangle.GetVertex3();

	REQUIRE(ver1.x == Approx(1));
	REQUIRE(ver1.y == Approx(1));
	REQUIRE(ver2.x == Approx(10));
	REQUIRE(ver2.y == Approx(10));
	REQUIRE(ver3.x == Approx(4));
	REQUIRE(ver3.y == Approx(5));

	REQUIRE(triangle.GetFillColour() == fillColour);
}

SCENARIO("Test with class CTriangle : overflow")
{
	constexpr double
		x1
		= std::numeric_limits<double>::max(),
		y1 = std::numeric_limits<double>::max(),
		x2 = std::numeric_limits<double>::max(), y2 = std::numeric_limits<double>::min(),
		x3 = std::numeric_limits<double>::min(), y3 = std::numeric_limits<double>::min();
	const uint32_t outlineColour = UINT32_MAX, fillColour = UINT32_MAX;

	CTriangle triangle({ x1, y1 }, { x2, y2 }, { x3, y3 }, outlineColour, fillColour);

	REQUIRE(isnan(triangle.GetArea()));
	REQUIRE(triangle.GetOutlineColour() == outlineColour);
	REQUIRE(triangle.GetFigureType() == "triangle");
	REQUIRE(isinf(triangle.GetPerimeter()));

	Point ver1 = triangle.GetVertex1(), ver2 = triangle.GetVertex2(), ver3 = triangle.GetVertex3();

	REQUIRE(ver1.x == Approx(std::numeric_limits<double>::max()));
	REQUIRE(ver1.y == Approx(std::numeric_limits<double>::max()));
	REQUIRE(ver2.x == Approx(std::numeric_limits<double>::max()));
	REQUIRE(ver2.y == Approx(std::numeric_limits<double>::min()));
	REQUIRE(ver3.x == Approx(std::numeric_limits<double>::min()));
	REQUIRE(ver3.y == Approx(std::numeric_limits<double>::min()));

	REQUIRE(triangle.GetFillColour() == fillColour);
}

SCENARIO("Test Point")
{
	Point point1({ 10, 10 });
	Point point2({ 20, 20 });
	REQUIRE(GetDistance(point1, point2) == Approx(14.1421356237));
}

SCENARIO("Test class ShapeController rectangle")
{
	std::vector<std::shared_ptr<IShape>> shapes;
	std::stringstream in("rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00\n");
	std::stringstream out("");
	ShapeController shapeController(shapes, in, out);
	shapeController.Start();

	REQUIRE(shapes.begin()->get()->GetFigureType() == "rectangle");
	REQUIRE(shapes.begin()->get()->GetArea() == Approx(1240.28));
	REQUIRE(shapes.begin()->get()->GetPerimeter() == Approx(142.2));
}

SCENARIO("Test class ShapeController line segment")
{
	std::vector<std::shared_ptr<IShape>> shapes;
	std::stringstream in("linesegment 1 1 5 5 ff0000\n");
	std::stringstream out("");
	ShapeController shapeController(shapes, in, out);
	shapeController.Start();

	REQUIRE(shapes.begin()->get()->GetFigureType() == "line");
	REQUIRE(shapes.begin()->get()->GetArea() == Approx(0));
	REQUIRE(shapes.begin()->get()->GetPerimeter() == Approx(5.6568542495));
}

SCENARIO("Test class ShapeController triangle")
{
	std::vector<std::shared_ptr<IShape>> shapes;
	std::stringstream in("triangle 10 -1 5 6 10 10 ff0000 00ff00\n");
	std::stringstream out("");
	ShapeController shapeController(shapes, in, out);
	shapeController.Start();

	REQUIRE(shapes.begin()->get()->GetFigureType() == "triangle");
	REQUIRE(shapes.begin()->get()->GetArea() == Approx(27.5));
	REQUIRE(shapes.begin()->get()->GetPerimeter() == Approx(26.0054495045));
}

SCENARIO("Test class ShapeController circle")
{
	std::vector<std::shared_ptr<IShape>> shapes;
	std::stringstream in("circle 10 10 15 ff0000 00ff00\n");
	std::stringstream out("");
	ShapeController shapeController(shapes, in, out);
	shapeController.Start();

	REQUIRE(shapes.begin()->get()->GetFigureType() == "circle");
	REQUIRE(shapes.begin()->get()->GetArea() == Approx(706.8583470577));
	REQUIRE(shapes.begin()->get()->GetPerimeter() == Approx(94.2477796077));
}

SCENARIO("Test class ShapeController")
{
	std::vector<std::shared_ptr<IShape>> shapes;
	std::stringstream in("circle 10 10 15 ff0000 00ff00\n"
						 "triangle 10 -1 5 6 10 10 ff0000 00ff00\n"
						 "linesegment 1 1 5 5 ff0000\n"
						 "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00\n"
						 "cone 10.3 20.15 30.7 40.4 ff0000 00ff00\n");
	std::stringstream out("");
	ShapeController shapeController(shapes, in, out);
	shapeController.Start();

	REQUIRE(shapes.size() == 4);

	REQUIRE(shapes.begin()->get()->GetFigureType() == "circle");
	REQUIRE(shapes.begin()->get()->GetArea() == Approx(706.8583470577));
	REQUIRE(shapes.begin()->get()->GetPerimeter() == Approx(94.2477796077));

	REQUIRE((shapes.begin() + 1)->get()->GetFigureType() == "triangle");
	REQUIRE((shapes.begin() + 1)->get()->GetArea() == Approx(27.5));
	REQUIRE((shapes.begin() + 1)->get()->GetPerimeter() == Approx(26.0054495045));

	REQUIRE((shapes.begin() + 2)->get()->GetFigureType() == "line");
	REQUIRE((shapes.begin() + 2)->get()->GetArea() == Approx(0));
	REQUIRE((shapes.begin() + 2)->get()->GetPerimeter() == Approx(5.6568542495));

	REQUIRE((shapes.begin() + 3)->get()->GetFigureType() == "rectangle");
	REQUIRE((shapes.begin() + 3)->get()->GetArea() == Approx(1240.28));
	REQUIRE((shapes.begin() + 3)->get()->GetPerimeter() == Approx(142.2));
}