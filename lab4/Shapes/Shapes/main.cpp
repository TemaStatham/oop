#include "ShapeController.h"
// #include <SFML/Graphics.hpp>
#include <fstream>

int main()
{
	std::ifstream inF1("figures.txt");
	std::vector<std::shared_ptr<IShape>> shapes;
	ShapeController shapeController(shapes, inF1, std::cout);

	shapeController.Start();

	/*sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}*/

	return 0;
}
