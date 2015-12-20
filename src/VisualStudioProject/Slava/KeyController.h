#ifndef KEYCONTROLLER_H
#define KEYCONTROLLER_H
#include "IController.h"
#include "Character.h"
#include <SFML\Graphics.hpp>
#define ATTACK_LENGTH 300

namespace slava
{

	class KeyController : virtual public IController
	{
	private:
		sf::Clock clock;
		
	public:
		// ~KeyController() {};

		void control(Character* character) {

			if (character->getStats()->health < 1) {
				character->getStats()->health += 0.0001 * character->getStats()->level;
			}
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				character->moveDown();
			}
			else {
				character->stopDown();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				character->moveUp();
			}
			else {
				character->stopUp();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				character->moveRight();
			}
			else {
				character->stopRight();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				character->moveLeft();
			}
			else {
				character->stopLeft();
			}

			if (clock.getElapsedTime().asMilliseconds() > ATTACK_LENGTH) {
				character->isAttack = false;
				// sf::Time t1 = clock.restart();
				// character->hit();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (clock.getElapsedTime().asMilliseconds() > ATTACK_LENGTH) {
					character->isAttack = true;
					sf::Time t1 = clock.restart();
					// character->hit();
				}
				
			}
		}
	};

}

#endif