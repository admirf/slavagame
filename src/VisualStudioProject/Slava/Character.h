#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML\Graphics.hpp>
#include "IController.h"
#include "Stats.h"

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

		Stats* stats;

		// Ogranicenje za ubrzanje da ne bi u beskonacnost ubrzavo
		const double limit = 2;
		
		
		IController* controller;

	public:

		Character();
		Character(sf::Texture*);
		void init();
		Stats* getStats();
		sf::Sprite* getSprite();
		void setStats(Stats*);

		void setTexture(sf::Texture*);
		void draw(sf::RenderWindow&);

		void moveLeft();
		void moveRight();
		void moveDown();
		void moveUp();
		void stopUp();
		void stopDown();
		void stopLeft();
		void stopRight();

		void levelUp();
		void setController(IController*);
		void control();

		sf::Texture* getTexture();
		~Character();
	};

}

#endif