#ifndef KEY_CONTROLLER_H
#define KEY_CONTROLLER_H

#include "IController.h"
#include "Character.h"
#include "GameWorld.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#define ATTACK_LENGTH 300

namespace slava
{

	// KeyController klasa je implementacija IController interfejsa, kao sto ime kaze ovdje implementiramo
	// mehaniku kontrole main charactera tastaturom

	class KeyController : virtual public IController
	{
	private:
		sf::Clock clock;
		
	public:
		// ~KeyController() {};

		// Evo je control metoda
		void control(Character* character) {

			int x = character->getSprite()->getPosition().x;
			int y = character->getSprite()->getPosition().y;

			// std::cout << x << ':' << y << " in RawMap\n";

			// Regeneracija healtha u ovisnosti levela igraca
			if (character->getStats()->health < 1) {
				character->getStats()->health += 0.0001 * character->getStats()->level;
			}
			
			// Obicna kontrola kretnje, ako tipka nije stisnuta treba zaustavljat karakter u tom smjeru
			// Ove provjere valid movement point ovo ja sad cisto onako da vidim bil funkcionisalo i evo bi
			// naravno ova sad implementacija za koliziju je dosta neprecizna i treba za svaki smjer napravit posebno provjeru mozel se ic dalje
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && character->isValidMovementPoint(x, y + 2)) {
				character->moveDown();
			}
			else {
				character->stopDown();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && character->isValidMovementPoint(x + 1, y)) {
				character->moveRight();
			}
			else {
				character->stopRight();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && character->isValidMovementPoint(x, y - 2)) {
				character->moveUp();
			}
			else {
				character->stopUp();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && character->isValidMovementPoint(x - 1, y)) {
				character->moveLeft();
			}
			else {
				character->stopLeft();
			}


			// ATTACK_LENGTH je duzina u milisekundama koliko traje napad
			// Ako je proslo to vrijeme stavljamo da karakter nije u Attack modu
			if (clock.getElapsedTime().asMilliseconds() > ATTACK_LENGTH) {
				character->isAttack = false;
				// sf::Time t1 = clock.restart();
				// character->hit();
			}

			// Ako je igrac stisnuo space i vrijeme od proslog napada je isteklo
			// Igramo animaciju udarca koja je indexirana na nuli
			// Stavljamo da je character u Attack modu
			// restartujemo sat koji mjeri vrijeme od zadnjeg napada
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (clock.getElapsedTime().asMilliseconds() > ATTACK_LENGTH) {
					character->playAnimation(0);
					character->isAttack = true;
					sf::Time t1 = clock.restart();
					// character->getGameWorld()->getNotification()->play("You hit the bastard!");
					// character->hit();
				}
				
			}
		}
	};

}

#endif