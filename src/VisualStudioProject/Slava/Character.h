#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML\Graphics.hpp>
#include "IController.h"

namespace slava
{

	sf::Texture* load_texture(const char*);

	class Character : sf::Transformable
	{
	private:
		sf::Texture* texture;
		sf::Sprite* sprite;
		double vX;
		double vY;
		double acceleration = 0.5;
		// Ogranicenje za ubrzanje da ne bi u beskonacnost ubrzavo
		const double limit = 2;
		// level ide po 0.25 napredak pa cemo mnozit sa nekim stvarima, lakse nego kompleksno levelovanje
		double level;
		IController* controller;

	public:

		Character();
		Character(sf::Texture*);

		void set_texture(sf::Texture*);
		void draw(sf::RenderWindow&);

		void move_left();
		void move_right();
		void move_down();
		void move_up();
		void stop_up();
		void stop_down();
		void stop_left();
		void stop_right();

		void level_up();
		void set_controller(IController*);
		void control();

		sf::Texture* get_texture();
		~Character();
	};

}

#endif