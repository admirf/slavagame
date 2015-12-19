#include <SFML/Graphics.hpp>
#include <memory>
#include "Character.h"
#include "KeyController.h"

using namespace std;
using namespace slava;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 640), "Slava");
	window.setVerticalSyncEnabled(true);

	auto character = make_shared<Character>();
	character->set_texture(slava::load_texture("Main-Character.png"));
	character->set_controller(new KeyController());
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			character->control();
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				character->move_down();
			}
			else {
				character->stop_down();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				character->move_up();
			}
			else {
				character->stop_up();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				character->move_right();
			}
			else {
				character->stop_right();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				character->move_left();
			}
			else {
				character->stop_left();
			}*/
			
			

		}

		window.clear();
		character->draw(window);
		window.display();
	}


	return 0;
}