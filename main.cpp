#include <iostream>
#include <thread>
#include <atomic>
#include <SFML/Graphics.hpp>


#include "Grille.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

std::atomic<bool> stopApp;
struct toDo
{
    bool yes = false;
    int x;
    int y;
};

toDo todo;
void runGraphicThread(Grille& grille, sf::RenderWindow& window);

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
	grille.synchroniserResult();


	window.setActive(false);
	std::thread gfx(runGraphicThread, std::ref(grille), std::ref(window));


	//Commands
	std::string command;
	while (window.isOpen() && !stopApp)
	{
			using std::cin;
			using std::cout;
			using std::endl;

			if(todo.yes)
			{
                    grille.move(todo.x, todo.y);
                    cout << todo.x << ' ' << todo.y << endl;
                    todo.yes = false;
			}

			cin >> command;
			if (command == "quit" || command == "q" || command== "leave" || command == "l")
				stopApp = true;
			else if (command == "resize")
			{
				int x, y;
				cout << "Entrez les dimensions : " << endl;
				cin >> x >> y;
				grille.resize(x, y);
			}
			else if (command == "show")
			{
				cout << grille;
			}
			else if (command == "complete")
			{
				grille.computeRange(1,grille.getH()-1);
			}
			else if (command == "move")
			{
				int x,y;
				cin >> x >> y;
				grille.move(x,y);
			}
			else if (command == "solve")
			{

				grille.solve();
				LOG(INFO) << "Grille résolue. Nombre de solutions : " << grille.getSolutions().size();
			}
			else if (command == "seed")
			{
					unsigned long seed;
					cin >> seed;
					grille.useSeed(seed);
			}
			else if (command == "solutions")
			{
				for (auto e : grille.getSolutions())
				cout << e << endl;
			}
			else if (command == "save")
			{
				grille.saveSolutions();
			}
	}

	gfx.join();

	return 0;
}


void runGraphicThread(Grille& grille, sf::RenderWindow& window)
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

                if (event.type == sf::Event::MouseButtonPressed)
                    {
                        auto winPos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                        auto worldPos = window.mapPixelToCoords(winPos);
                        worldPos.x /= 100;
                        worldPos.y /= 100;
                        grille.move(worldPos.x, worldPos.y); //CONST-Correctness :(
                        //todo.yes = true;
                        //todo.x = worldPos.x;
                        //todo.y = worldPos.y;
                    }
			}

		window.clear(sf::Color(120,120,120));

		window.draw(grille);
		window.display();
		}

		window.close();
		return;

}
