#pragma once
#ifndef KEYCONTROLLER_H
#define KEYCONTROLLER_H
#include "IController.h"
#include "Character.h"
#include <SFML\Graphics.hpp>

namespace slava
{

	class KeyController : virtual public IController
	{
	public:
		// ~KeyController() {};

		void control(Character* character) {

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
		}
	};

}

#endif