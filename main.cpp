#include <iostream>
#include <SFML/Graphics.hpp>


#include "Grille.h"

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Default, settings);

	///Grille
	Grille grille(4,4);
	grille.checked[1] = true;
	grille.checked[7] = true;
	grille.checked[8] = true;
//	grille.checked[14] = true;


	std::cout << grille;

	while (window.isOpen())
	{
		sf::Event event;
        	while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
			window.close();
		}

	window.clear(sf::Color(120,120,120));

	window.draw(grille);
	window.display();
	}

	return 0;
}
