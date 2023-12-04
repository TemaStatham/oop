#include "ICanvasDrawable.h"
#include "IShape.h"
#include <vector>
#pragma once

class CCanvasDrawable : public ICanvasDrawable
{
public:
	void Draw(ICanvas& Canvas) const;

private:
	std::vector<IShape> shapes;
};