#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <SFML\Graphics.hpp>
#include "IController.h"
#include "Stats.h"
#include "Animation.h"
#include "Map.h"
#include "Dialog.h"
#include "Inventory.h"
#include <vector>
#include <memory>
#include <fstream>

namespace slava
{
	class Animation;
	class GameWorld;

	enum skills { STRENGTH, ENDURANCE, MANA };

	typedef std::shared_ptr<GameWorld> GameWorldPtr;
	/*
	Character je fancy klasa koja wrappuje sf::Sprite i nasljedjuje sf::Transformable (da bi se lakse pomjero karakter)
	Character enkapsulira reference na Sprite i Teksturu a uz to sadrzi vektor animacija koje se mogu pustat o animacijama kasnije
	Najbitnije je razumit kretanje koje koristi jednostavno ubrzavanje koje ima limit postatvljen u Stats referenci (Stats je struct koji
	drzi osnovne podatke o karakteru tipa koji je level, kolko healtha ima itd.). Limit se zapravo zasad izracunava mnozenjem tog limita sa
	levelom karaktera al to se da lagano promijenit
	Uglavnom karakter podrzava kretanje u lijevo, desno, dole, gore e sad je fazon sto je to kretanje kontinuirano pa postoje
	posebno metode za zaustavljanje stop metode
	Ima i metoda moveRandom koja pokrene karakter u random smjer
	U ovoj klasi ima mnogo metoda tipa gotHit(bool) koja oznacava da je karakter udaren ili metoda isDead() koja vraca da li je health ispod nule
	ima cak i osobinu isAttack koja oznacava da je karakter u toku napada, a to je korisna osobina kod kontrolera
	Sada najbitniji dio svega jesu kontroleri, za svaki karakter je bitno postavit klasu koja implementira IController interfejs
	i onda u main loopu i event loopu (ovisno o tom kako je kontroliran) treba pozivat control() metodu.
	E sada da se vratim ukratko na animacije, animacije se dodaju u vektor, i onda se pustaju tako sto se index proslijedi kao argument
	za metodu playAnimation(), takodje bitno je ponavljam animacije se moraju update-ovat u main loopu pa se treba i pozivat updateAnimation(index)
	*/

	struct Position { int x; int y; };
	typedef std::shared_ptr<sf::Texture> TexturePtr;
	typedef std::shared_ptr<Character> CharacterPtr;

	class Character : public sf::Transformable
	{
	private:

		const char* id;
		GameWorld* world;
		std::vector<Animation> animations;
		std::vector<int> inventory;
		Map* worldMap;
		bool mapIsSet = false;
		TexturePtr texture;
		TexturePtr blockTexture;
		sf::Sprite* sprite;
		// sf::Color originalColor;
		// std::vector< std::shared_ptr<Character> > otherCharacters;

		double vX;
		double vY;

		sf::Clock clock;
		bool hit = false;

		Stats* stats;
		bool hasLeveledUp = false;

		// Ogranicenje za ubrzanje da ne bi u beskonacnost ubrzavo

		IController* controller;
		std::shared_ptr<DialogNode> dialog;


		bool isWalkableVertical(int, int, int);
		bool isWalkableHorizontal(int, int, int);

	public:
		bool isAttack;
		bool isBlock;
		bool isManaAttack;
		double limit = 2;
		ItemPtr currentWeapon;
		ItemPtr currentShield;
		Character(const char*);
		Character(const char*, sf::Texture*);
		void init();
		Stats* getStats();
		sf::Sprite* getSprite();
		void setStats(Stats*);
		const char* getID();

		void setGameWorld(GameWorld*);
		GameWorld* getGameWorld();
		void setTexture(TexturePtr);
		void setMap(Map*);
		Map* getMap();
		void draw(sf::RenderWindow&);
		void addAnimation(Animation&);
		void playAnimation(int);
		void updateAnimation(int);
		void setDialog(std::shared_ptr<DialogNode>&);
		std::shared_ptr<DialogNode> getDialog();
		int getNumberOfAnimations();

		void moveRandom();
		void moveLeft();
		void moveRight();
		void moveDown();
		void moveUp();
		void stopUp();
		void stopDown();
		void stopLeft();
		void stopRight();
		void stopMovement();
		bool canMoveUp();
		bool canMoveDown();
		bool canMoveRight();
		bool canMoveLeft();
		bool isDead();
		void alive();
		void gotHit(bool);
		bool canBeHere(int, int);
		Position getPositionOnTile(int);
		void block();
		void unblock();
		void setBlockTexture(TexturePtr);
        void exportCharStats(std::string, int);
        bool importCharStats(std::string, int);
		/*
		bool collision(std::shared_ptr<Character>);
		void addCollidableCharacter(std::shared_ptr<Character>);
		void clearCollidableCharacters();
		bool notColliding();
		*/

		void addItem(int, int);
		void addItem(int);
		int getItem(int);
		void removeItem(int);
        bool canAddItem();

		void levelUp();
		void increaseSkill(skills);
		bool canIncreaseSkill();
		void setController(IController*);
		void control();

		TexturePtr getTexture();
		~Character();
	};

}

#endif
