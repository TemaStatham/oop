#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"
#include <functional>
#include <map>
#include <memory>
#include <vector>

#pragma once

class ShapeController
{
public:
	ShapeController(std::vector<std::shared_ptr<IShape>>& shapes, std::istream& in, std::ostream& out);

	void Start();

	~ShapeController() = default;

private:
	using Handler = std::function<std::shared_ptr<IShape>()>;

	std::shared_ptr<IShape> CreateShape(const std::string& str) const;
	void PrintShapeInfoWithLargestArea() const;
	void PrintShapeInfoWithSmallestPerimeter() const;

	std::shared_ptr<CTriangle> CreateTriangle() const;
	std::shared_ptr<CRectangle> CreateRectangle() const;
	std::shared_ptr<CCircle> CreateCircle() const;
	std::shared_ptr<CLineSegment> CreateLineSegment() const;

	using ActionMap = std::map<std::string, Handler>;

	uint32_t GetColor(const std::string& colorAsString) const;

	void Help();

	std::vector<std::shared_ptr<IShape>>& m_shapes;
	std::istream& m_in;
	std::ostream& m_out;

	const ActionMap m_actionMap;
};
