#ifndef __KEY_CONTROLLER_H
#define __KEY_CONTROLLER_H

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

			// Provjeri jel skupljeno spa za level up
			int lvl = character->getStats()->level;
			if ((lvl + lvl / 4) * 1000 < character->getStats()->sp) {
				character->levelUp();
				// otvori Skill View
				character->getGameWorld()->getUI("skillUI")->active = true;
				character->getGameWorld()->pause();
			}

			int x = character->getSprite()->getPosition().x;
			int y = character->getSprite()->getPosition().y;

			std::cout << x << ':' << y << " in RawMap\n";

			// Regeneracija healtha u ovisnosti levela igraca
			if (character->getStats()->health < 1) {
				character->getStats()->health += 0.0001 * character->getStats()->level;
			}
			// Regeneracija mane u ovisnosti od mane igraca
			if (character->getStats()->mana_timer < 1) {
				character->getStats()->mana_timer += 0.0001 * character->getStats()->mana;
			}
			
			// Obicna kontrola kretnje, ako tipka nije stisnuta treba zaustavljat karakter u tom smjeru
			// Ove provjere valid movement point ovo ja sad cisto onako da vidim bil funkcionisalo i evo bi
			// naravno ova sad implementacija za koliziju je dosta neprecizna i treba za svaki smjer napravit posebno provjeru mozel se ic dalje
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && character->canMoveDown()) {
				character->moveDown();
			}
			else {
				character->stopDown();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && character->canMoveRight()) {
				character->moveRight();
			}
			else {
				character->stopRight();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && character->canMoveUp()) {
				character->moveUp();
			}
			else {
				character->stopUp();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && character->canMoveLeft()) {
				character->moveLeft();
			}
			else {
				character->stopLeft();
			}

			// Pauza na escape
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				character->getGameWorld()->getUI("pauseUI")->active = true;
				character->getGameWorld()->pause();
			}

			// informacije o current weapon i shield
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
				std::string s = "Current weapon: " + character->currentWeapon->name + "\nCurrent shield: " + character->currentShield->name;
				character->getGameWorld()->getNotification()->play(s.c_str());
			}

			// ATTACK_LENGTH je duzina u milisekundama koliko traje napad
			// Ako je proslo to vrijeme stavljamo da karakter nije u Attack modu
			if (clock.getElapsedTime().asMilliseconds() > ATTACK_LENGTH) {
				character->isAttack = false;
				character->isManaAttack = false;
				// sf::Time t1 = clock.restart();
				// character->hit();
			}

			// Ako je igrac uradio lijevi klik i vrijeme od proslog napada je isteklo
			// Igramo animaciju udarca koja je indexirana na nuli
			// Stavljamo da je character u Attack modu
			// restartujemo sat koji mjeri vrijeme od zadnjeg napada
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (clock.getElapsedTime().asMilliseconds() > ATTACK_LENGTH) {
					character->playAnimation(0);
					character->isAttack = true;
					character->isBlock = false;
					sf::Time t1 = clock.restart();
					// character->getGameWorld()->getNotification()->play("You hit the bastard!");
					// character->hit();
				}
				
			}

			// Ako je igras udario srednji mis radimo isto ko i za obicni napad samo mana napad
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && character->getStats()->mana_timer >= 1) {
				if (clock.getElapsedTime().asMilliseconds() > ATTACK_LENGTH) {
					character->playAnimation(1);
					character->isManaAttack = true;
					character->isBlock = false;
					character->getStats()->mana_timer = 0;
					sf::Time t1 = clock.restart();
					// character->getGameWorld()->getNotification()->play("You hit the bastard!");
					// character->hit();
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				character->block();
				character->isAttack = false;
				// character->isBlock = true;
				return;
				// character->getGameWorld()->getNotification()->play("Block mode");
			}
			else {
				character->unblock();
				// character->isBlock = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				character->getGameWorld()->getWindow()->setKeyRepeatEnabled(false);
				character->getGameWorld()->getUI("inventoryUI")->active = true;
				character->getGameWorld()->pause();
				return;
			}
			
		}
	};

}

#endif