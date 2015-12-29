#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Character.h"
#include "EnemyController.h"
#include "Utility.h"

namespace slava 
{
	// Klasa za pravljenje predefinisanih enemija TODO: Dodat ovdje animaciju udaranja indeksiranu na nuli
	class EnemyFactory
	{
	public:
		static std::shared_ptr<Character> createBasicEnemy(const char* id, std::shared_ptr<Character> player, int x, int y) {
			auto controller = new EnemyController(player);
			controller->reattack = sf::milliseconds(2000);
			auto enemy = std::make_shared<Character>(id);
			enemy->setController(controller);
			enemy->limit = 1.2;
			enemy->setTexture(loadTexture("Main-Character.png"));
			enemy->getSprite()->setPosition(x, y);
			return enemy;
		}
	};

}

#endif
