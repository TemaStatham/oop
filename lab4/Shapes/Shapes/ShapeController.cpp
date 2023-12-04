#include "ShapeController.h"
#include <algorithm>

ShapeController::ShapeController(std::vector<std::shared_ptr<IShape>>& shapes, std::istream& in, std::ostream& out)
	: m_shapes(shapes)
	, m_in(in)
	, m_out(out)
	, m_actionMap({
		  { "triangle", [this]() {
			   return CreateTriangle();
		   } },
		  { "rectangle", [this]() {
			   return CreateRectangle();
		   } },
		  { "circle", [this]() {
			   return CreateCircle();
		   } },
		  { "linesegment", [this]() {
			   return CreateLineSegment();
		   } },
	  })
{
}

void ShapeController::Start()
{
	Help();
	std::string typeOfFigureAsString;
	while (m_in >> typeOfFigureAsString)
	{
		try
		{
			m_shapes.push_back(CreateShape(typeOfFigureAsString));
			m_out << "The shape was saved successfully" << std::endl;
		}
		catch (const std::exception& e)
		{
			m_out << e.what() << std::endl;
			std::string garbage;
			getline(m_in, garbage);
		}
	}

	PrintShapeInfoWithLargestArea();
	PrintShapeInfoWithSmallestPerimeter();
}

std::shared_ptr<CTriangle> ShapeController::CreateTriangle() const
{
	std::vector<Point> trianglePoints;
	for (size_t i = 0; i < 3; i++)
	{
		double x, y;
		m_in >> x >> y;
		if (m_in.fail())
		{
			throw std::invalid_argument("Not enough arguments");
		}
		trianglePoints.push_back({ x, y });
	}

	char ch;
	m_in.get(ch);
	if (m_in.fail() || ch == '\n')
	{
		CTriangle triangle(trianglePoints[0], trianglePoints[1], trianglePoints[2], uint32_t(), uint32_t());
		return std::make_shared<CTriangle>(triangle);
	}
	std::string outlineStringColour, fillStringColour;
	m_in >> outlineStringColour >> fillStringColour;
	uint32_t outlineColour = GetColor(outlineStringColour);
	uint32_t fillColour = GetColor(fillStringColour);

	CTriangle triangle(trianglePoints[0], trianglePoints[1], trianglePoints[2], outlineColour, fillColour);

	return std::make_shared<CTriangle>(triangle);
}

std::shared_ptr<CRectangle> ShapeController::CreateRectangle() const
{
	double x, y, width, height;
	std::string outlineStringColour, fillStringColour;
	m_in >> x >> y >> width >> height;
	if (m_in.fail())
	{
		throw std::invalid_argument("Not enough arguments");
	}
	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("Invalid width or height params");
	}
	char ch;
	m_in.get(ch);
	if (m_in.fail() || ch == '\n')
	{
		CRectangle rectangle({ x, y }, width, height, uint32_t(), uint32_t());
		return std::make_shared<CRectangle>(rectangle);
	}
	m_in >> outlineStringColour >> fillStringColour;
	uint32_t outlineColour = GetColor(outlineStringColour);
	uint32_t fillColour = GetColor(fillStringColour);

	CRectangle rectangle({ x, y }, width, height, outlineColour, fillColour);

	return std::make_shared<CRectangle>(rectangle);
}

std::shared_ptr<CCircle> ShapeController::CreateCircle() const
{
	double x, y, radius;
	std::string outlineStringColour, fillStringColour;
	m_in >> x >> y >> radius;
	if (m_in.fail())
	{
		throw std::invalid_argument("Not enough arguments");
	}
	if (radius < 0)
	{
		throw std::invalid_argument("Invalid radius param");
	}
	char ch;
	m_in.get(ch);
	if (m_in.fail() || ch == '\n')
	{
		CCircle circle({ x, y }, radius, uint32_t(), uint32_t());
		return std::make_shared<CCircle>(circle);
	}
	m_in >> outlineStringColour >> fillStringColour;
	uint32_t outlineColour = GetColor(outlineStringColour);
	uint32_t fillColour = GetColor(fillStringColour);

	CCircle circle({ x, y }, radius, outlineColour, fillColour);

	return std::make_shared<CCircle>(circle);
}

std::shared_ptr<CLineSegment> ShapeController::CreateLineSegment() const
{
	double x1, y1, x2, y2;
	std::string outlineStringColour;
	m_in >> x1 >> y1 >> x2 >> y2;
	if (m_in.fail())
	{
		throw std::invalid_argument("Not enough arguments");
	}
	char ch;
	m_in.get(ch);
	if (m_in.fail() || ch == '\n')
	{
		CLineSegment line({ x1, y1 }, { x2, y2 }, uint32_t());

		return std::make_shared<CLineSegment>(line);
	}
	m_in >> outlineStringColour;
	uint32_t outlineColour = GetColor(outlineStringColour);

	CLineSegment line({ x1, y1 }, { x2, y2 }, outlineColour);

	return std::make_shared<CLineSegment>(line);
}

uint32_t ShapeController::GetColor(const std::string& colorAsString) const
{
	try
	{
		uint32_t color = std::stoi(colorAsString, nullptr, 16);

		return color;
	}
	catch (...)
	{
		throw std::invalid_argument("Invalid color");
	}
}

void ShapeController::Help()
{
	m_out << "Commands : " << std::endl
		  << "\trectangle x y width height outlineStringColour fillStringColour" << std::endl
		  << "\ttriangle x1 y1 x2 y2 x3 y3 outlineStringColour fillStringColour" << std::endl
		  << "\tcircle x y radius outlineStringColour fillStringColour" << std::endl
		  << "\tlinesegment x1 y1 x2 y2 outlineStringColour" << std::endl;
}

void ShapeController::PrintShapeInfoWithLargestArea() const
{
	if (m_shapes.size() == 0)
	{
		m_out << "Shapes is empty" << std::endl;
		return;
	}

	auto maxAreaShape = std::max_element(m_shapes.begin(), m_shapes.end(), [](const auto& left, const auto& right) {
		return left->GetArea() < right->GetArea();
	});

	m_out << "Shape with largest area :" << std::endl;
	m_out << maxAreaShape->get()->ToString() << std::endl;
}

void ShapeController::PrintShapeInfoWithSmallestPerimeter() const
{
	if (m_shapes.size() == 0)
	{
		m_out << "Shapes is empty" << std::endl;
		return;
	}

	auto minPerimeterShape = std::min_element(m_shapes.begin(), m_shapes.end(), [](const auto& left, const auto& right) {
		return left->GetPerimeter() < right->GetPerimeter();
	});

	m_out << "Shape with smallest perimeter :" << std::endl;
	m_out << minPerimeterShape->get()->ToString() << std::endl;
}

std::shared_ptr<IShape> ShapeController::CreateShape(const std::string& typeOfFigureAsString) const
{
	auto it = m_actionMap.find(typeOfFigureAsString);
	if (it != m_actionMap.end())
	{
		return it->second();
	}

	throw std::invalid_argument("Invalid type of figure");
}
