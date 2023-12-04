#include "ICanvas.h"

#pragma once
// #include <SFML/Graphics.hpp>

class ICanvasDrawable
{
public:
	// virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Draw(ICanvas& Canvas) const = 0;
};
