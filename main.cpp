#include <iostream>
#include <thread>
#include <atomic>
#include <SFML/Graphics.hpp>


#include "Grille.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

std::atomic<bool> stopApp;

void runGraphicThread(const Grille& grille, sf::RenderWindow& window);

int main()
{
	LOG(INFO) << "Lancement";
	stopApp = false;

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	sf::RenderWindow window(sf::VideoMode(200, 200), "Math en Jeans", sf::Style::Default, settings);

	///Grille
	Grille grille(4,4);
	grille.checked[1] = true;
//	grille.checked[7] = true;
//	grille.checked[8] = true;
//	grille.checked[14] = true;
	grille.synchroniserResult();
	grille.computeRange(1,3);

	std::cout << grille;
	window.setActive(false);

	std::thread gfx(runGraphicThread, grille, std::ref(window));


	//Commands
	std::string command;
	while (window.isOpen() && !stopApp)
	{
			using std::cin;
			using std::cout;
			using std::endl;

			cin >> command;
			if (command == "quit" || command == "q" || command== "leave" || command == "l")
				stopApp = true;
	}

	gfx.join();

	return 0;
}


void runGraphicThread(const Grille& grille, sf::RenderWindow& window)
{
		window.setActive(true);

		while (window.isOpen() && !stopApp)
		{
			sf::Event event;
	        	while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					stopApp = true;
				else if (event.type == sf::Event::KeyPressed)
					if(event.key.code == sf::Keyboard::Key::Escape) stopApp = true;
			}

		window.clear(sf::Color(120,120,120));

		window.draw(grille);
		window.display();
		}

		window.close();
		return;

}
