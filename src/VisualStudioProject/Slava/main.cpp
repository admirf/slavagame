#include <SFML/Graphics.hpp>
#include <memory>
#include "Character.h"
#include "KeyController.h"
#include "HUD.h"
#include "Camera.h"
#include "EnemyFactory.h"
#include <iostream>

using namespace std;
using namespace slava;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Slava");
	window.setVerticalSyncEnabled(true);

	window.setKeyRepeatEnabled(true);

	auto character = make_shared<Character>();
	character->setTexture(slava::load_texture("Main-Character.png"));
	character->setController(new KeyController());
	character->getStats()->health = 0.5;
	character->getStats()->sp = 20000;

	auto enemy = EnemyFactory::createBasicEnemy(character, 200, 400);

	// character->addCollidableCharacter(enemy);

	HUD hud(character->getStats(), "sgs.ttf");
	Camera cam(character->getSprite());
	cam.setAcceleration(2);
	cam.setOffset(200, 100);
	sf::View customView(sf::FloatRect(0, 0, 1000, 600));
	cam.bindHUD(&hud);

	sf::CircleShape shape(50);
	shape.setPosition(400, 20);
	shape.setFillColor(sf::Color(100, 250, 50));
	sf::CircleShape shape2(50);
	shape2.setPosition(480, 20);
	shape2.setFillColor(sf::Color(100, 250, 50));
	
	while (window.isOpen())
	{
		// cout << character->isAttack << endl;
		cam.update(customView);
		// customView.setCenter(character->getSprite()->getPosition());
		sf::Event event;
		enemy->control();
		character->control();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			
			character->control();
			enemy->control();
			

		}
		// cout << character->isHit << endl;
		window.clear();
		window.draw(shape);
		window.draw(shape2);

		if (!enemy->isDead()) {
			enemy->draw(window);
		}
		
		character->draw(window);
		
		hud.draw(window);
		window.setView(customView);
		window.display();
	}


	return 0;
}