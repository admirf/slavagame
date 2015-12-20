#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
#include "EnemyController.h"

namespace slava 
{

	class EnemyFactory
	{
	public:
		static std::shared_ptr<Character> createBasicEnemy(std::shared_ptr<Character> player, int x, int y) {
			auto controller = new EnemyController(player);
			controller->reattack = 1;
			auto enemy = std::make_shared<Character>();
			enemy->setController(controller);
			enemy->limit = 1.2;
			enemy->setTexture(slava::loadTexture("Main-Character.png"));
			enemy->getSprite()->setPosition(x, y);
			return enemy;
		}
	};

}

#endif
