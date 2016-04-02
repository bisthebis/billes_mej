#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;


	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Default, settings);
   	sf::CircleShape shape(100.f);
   	shape.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		sf::Event event;
        	while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
			window.close();
		}

	window.clear();
	window.draw(shape);
	window.display();
	}

	return 0;
}
