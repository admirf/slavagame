#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML\Graphics.hpp>
#include "IController.h"
#include "Stats.h"
#include <vector>
#include <memory>

namespace slava
{

	sf::Texture* load_texture(const char*);

	class Character : sf::Transformable
	{
	private:
		sf::Texture* texture;
		sf::Sprite* sprite;
		sf::Color originalColor;
		std::vector< std::shared_ptr<Character> > otherCharacters;

		double vX;
		double vY;

		std::time_t lastTimeHit;

		Stats* stats;

		// Ogranicenje za ubrzanje da ne bi u beskonacnost ubrzavo
		
		IController* controller;

	public:
		bool isAttack;
		double limit = 2;
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
		bool isDead();
		void gotHit();
		
		bool collision(std::shared_ptr<Character>);
		void addCollidableCharacter(std::shared_ptr<Character>);
		void clearCollidableCharacters();
		bool notColliding();

		void levelUp();
		void setController(IController*);
		void control();

		sf::Texture* getTexture();
		~Character();
	};

}

#endif