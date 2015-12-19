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
			}
		}
	};

}

#endif