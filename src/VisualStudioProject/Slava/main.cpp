#include <SFML/Graphics.hpp>
#include <memory>
#include "Character.h"
#include "KeyController.h"
#include "HUD.h"
#include "Camera.h"
#include "EnemyFactory.h"
#include "Utility.h"
#include "Map.h"
#include "TileFactory.h"
#include <iostream>

using namespace std;
using namespace slava;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Slava");
	window.setVerticalSyncEnabled(true);

	window.setKeyRepeatEnabled(true);

	auto txt = loadTexture("tileset_1.png");

	Map map("mapa1.txt", txt, getMapSize("mapa1.txt"), 16);

	cout << "It reaches this" << endl;

	auto character = make_shared<Character>();
	character->setMap(&map);
	character->setTexture(loadTexture("Main-Character.png"));
	character->setController(new KeyController());
	character->getStats()->health = 0.5;
	character->getStats()->sp = 20000;

	// animacija udaranja
	vector<shared_ptr<sf::Texture>> textures;
	textures.push_back(loadTexture("main_cha_hit.png"));
	Animation anim(textures, sf::milliseconds(180));
	character->addAnimation(anim);

	/* // animacija hodanja
	vector<shared_ptr<sf::Texture>> texturesAnim2;
	texturesAnim2.push_back(loadTexture);*/

	auto enemy = EnemyFactory::createBasicEnemy(character, 200, 400);
	enemy->addAnimation(anim);

	HUD hud(character->getStats(), "sgs.ttf");
	Camera cam(character->getSprite());
	cam.setAcceleration(2);
	cam.setOffset(200, 100);
	sf::View customView(sf::FloatRect(0, 0, 1000, 600));
	// customView.zoom(0.7);
	cam.bindHUD(&hud);

	
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
			character->updateAnimation(0);
			enemy->control();
			enemy->updateAnimation(0);
			

		}
		character->updateAnimation(0);
		enemy->updateAnimation(0);
		// cout << character->isHit << endl;
		window.clear();
		map.draw(window);

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