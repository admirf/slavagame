#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include <memory>
#include "Character.h"

namespace slava
{

	/*
	Implementacija IController koja bi ko trebala da sadrzi mehaniku i AI ponasanja enemija, Idi na EnemyController.cpp da objasnim malo detaljnije
	*/

	class EnemyController: public virtual IController
	{
	private:
		CharacterPtr player;
		// sf::Time lastHit;
		sf::Clock clock1;
		bool hit = false;

	public:
		sf::Time reattack;
		EnemyController(CharacterPtr);
		void control(Character*);
	};

}

#endif
