#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML\Graphics.hpp>
#include "IController.h"
#include "Stats.h"
#include "Animation.h"
#include <vector>
#include <memory>

namespace slava
{
	class Animation;
	std::shared_ptr<sf::Texture> loadTexture(const char*);

	class Character : sf::Transformable
	{
	private:

		std::vector<Animation> animations;

		std::shared_ptr<sf::Texture> texture;
		sf::Sprite* sprite;
		sf::Color originalColor;
		std::vector< std::shared_ptr<Character> > otherCharacters;

		double vX;
		double vY;

		sf::Clock clock;
		bool hit = false;

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

		void setTexture(std::shared_ptr<sf::Texture>);
		void draw(sf::RenderWindow&);
		void addAnimation(Animation&);
		void playAnimation(int);
		void updateAnimation(int);

		void moveRandom();
		void moveLeft();
		void moveRight();
		void moveDown();
		void moveUp();
		void stopUp();
		void stopDown();
		void stopLeft();
		void stopRight();
		bool isDead();
		void gotHit(bool);
		
		bool collision(std::shared_ptr<Character>);
		void addCollidableCharacter(std::shared_ptr<Character>);
		void clearCollidableCharacters();
		bool notColliding();

		void levelUp();
		void setController(IController*);
		void control();

		std::shared_ptr<sf::Texture> getTexture();
		~Character();
	};

}

#endif