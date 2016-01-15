#include "EnemyController.h"
#include "GameWorld.h"
#include "EnemyFactory.h"
#include "Map.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

// U enemy konstruktor se postavlja referenca na igraca tj. Main charactera
slava::EnemyController::EnemyController(CharacterPtr player) {
	this->player = player;
}

void slava::EnemyController::primitiveMove(int whereX, int whereY, int safeZone, Character *enemy) {
	int x = enemy->getSprite()->getPosition().x;
	int y = enemy->getSprite()->getPosition().y;
	x += enemy->getSprite()->getGlobalBounds().width / 2;
	y += enemy->getSprite()->getGlobalBounds().height / 2;
	if (x < whereX - safeZone) {
		enemy->moveRight();
		enemy->stopLeft();
	}
	else if (x > whereX + safeZone) {
		enemy->moveLeft();
		enemy->stopRight();
	}
	else {
		enemy->stopLeft();
		enemy->stopRight();
	}

	if (y < whereY - safeZone) {
		enemy->moveDown();
		enemy->stopUp();
	}
	else if (y > whereY + safeZone) {
		enemy->moveUp();
		enemy->stopDown();
	}
	else {
		enemy->stopUp();
		enemy->stopDown();
	}
}

// Evo je genijalna control metoda
void slava::EnemyController::control(Character* enemy) {
	if (enemy->getMap() == nullptr) return;
	//std::cout<<"TU SAM"<<std::endl;
	// provjeri da li je enemy ubijen i ako jeste dodaj igracu sp-a
	if (enemy->isDead()) {
		return;
	}

	// Uzimamo poziciju main charactera tj. targeta
	int xTarget = player->getSprite()->getPosition().x;
	int yTarget = player->getSprite()->getPosition().y;

	// Uzimamo poziciju enemija
	int x = enemy->getSprite()->getPosition().x;
	int y = enemy->getSprite()->getPosition().y;

	// Dobivamo centar poziciju enemija
	x += enemy->getSprite()->getGlobalBounds().width / 2;
	y += enemy->getSprite()->getGlobalBounds().height / 2;
	// DObivamo centar poziciju targeta
	xTarget += player->getSprite()->getGlobalBounds().width / 2;
	yTarget += player->getSprite()->getGlobalBounds().height / 2;

	// Ovdje provjeravamo da li je proslo dovoljno vremena da se prebacimo opet u modus napada, tj radimo sta bi inace radili
	if (clock1.getElapsedTime() > reattack) {
		hit = false; // stavljamo flag, glupo sam ga nazvao, al eto ovaj flag govori da li je enemy zadao udarac ili nije
					 // Posto je vrijeme od zadnjeg dovoljno proslo stavljamo hit opet na false i ganjamo target sa ovim move-vima

	}
	// racunamo udaljenost od targeta
	double dist = std::sqrt((x - xTarget) * (x - xTarget) + (y - yTarget)*(y - yTarget));

	if (dist <= 150 * this->player->getStats()->mana && this->player->isManaAttack) {
		enemy->getStats()->health -= this->player->getStats()->mana * 0.05;
		enemy->gotHit(false);
	}

	if (dist<100) // ako je enemy "blizu" targeta, primitivno se krece
	{
		primitiveMove(xTarget, yTarget, 20, enemy);
		// ako je manja od 20 pixela i nismo uskoro zadali udarac targetu, zadaj udarac targetu
		// odigraj animaciju udarca koja je indexirana na nuli za enemije
		// smanji health igracu
		// javi igracu da je udaren gotHit(true) true se stavlja ako je character main character, ako nije stavlja se false
		// pokreni enemija u random smjeru
		// restartuj sat koji mjeri vrijeme od zadnjeg udarca
		if (dist <= 30 && !hit) {

			hit = true;
			enemy->playAnimation(0);
			if (!this->player->isBlock) {
				this->player->getStats()->health -= 0.1;
				this->player->gotHit(true);
			}
			enemy->moveRandom();
			clock1.restart();

		}

		// e sada provjeravamo da li je igrac udario nas, ako je udaljenost manja od 20 pixela i igrac je u attack modu
		// smanji enemiju health za neki faktor * igracev level
		// javi da je enemy udaren
		if (dist <= 30 && this->player->isAttack) {

			enemy->getStats()->health -= this->player->getStats()->strength * 0.01;
			enemy->gotHit(false);
			/* sf::Thread th(&Character::gotHit, enemy);
			th.launch(); */
			// enemy->gotHit();
		}
		// provjera za mana napad

	}
	else {
		if (dist<1500) {

			int tileSize = enemy->getMap()->getTileSize();
			//tileSize=16;
			slava::Coordinate destination = enemy->getMap()->getNextFromTo(Coordinate(x / tileSize, y / tileSize), Coordinate(xTarget / tileSize, yTarget / tileSize));
			//std::cout<<destination.x -(x/tileSize)<< " " <<destination.y -(y/tileSize)<< '\n';
			//std::cout<<x/tileSize - destination.x<< " " << y/tileSize - destination.y << '\n';
			int toCenter = tileSize / 2;
			primitiveMove(destination.x*tileSize + toCenter, destination.y*tileSize + toCenter, 0, enemy);
		}
		else {
			enemy->stopLeft();
			enemy->stopRight();
			enemy->stopDown();
			enemy->stopUp();
		}
	}

	if (enemy->isDead()) {
		int rnd = rand() % 200 + 1;
		rnd=rand()%100;
		std::string s = "Enemy looted.\n" + toString(rnd) + " Gold loot added to inventory.";
		if(rnd>50&&this->player->canAddItem()){
            if(rnd>75){
                s+="\nHealth potion added!";
                this->player->addItem(5);
            }else{
                s+="\nMana potion added!";
                this->player->addItem(6);
            }

		}

		this->player->getGameWorld()->getNotification()->play(s.c_str());
		// enemy->alive();
		// enemy->getSprite()->setPosition(0, 0);
		this->player->getStats()->sp += 200;
		this->player->getStats()->gold += rnd;

	}


	// std::cout << enemy->getStats()->health * 100 << std::endl;

}
