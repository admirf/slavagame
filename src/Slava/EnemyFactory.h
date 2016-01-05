#ifndef __ENEMY_FACTORY_H
#define __ENEMY_FACTORY_H

#include "Character.h"
#include "EnemyController.h"
#include "Utility.h"
#include "Animation.h"
#include <memory>
#include <vector>

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
			enemy->setTexture(loadTexture("Basic-Enemy.png"));
			enemy->getSprite()->setPosition(x, y);

			std::vector<std::shared_ptr<sf::Texture>> textures;
			textures.push_back(loadTexture("Basic-Enemy-Hit.png"));
			Animation anim("hit", textures, sf::milliseconds(180));
			enemy->addAnimation(anim);

			return enemy;
		}
	};

}

#endif
