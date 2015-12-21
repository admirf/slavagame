#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H
#include <memory>
#include "Character.h"

namespace slava
{

	class EnemyController: public virtual IController
	{
	private:
		std::shared_ptr<Character> player;
		// sf::Time lastHit;
		sf::Clock clock1;
		bool hit = false;

	public:
		time_t reattack;
		EnemyController(std::shared_ptr<Character>);
		void control(Character*);
	};

}

#endif
