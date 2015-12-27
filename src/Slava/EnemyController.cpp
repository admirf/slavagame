#include "EnemyController.h"
#include "GameWorld.h"
#include "EnemyFactory.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

// U enemy konstruktor se postavlja referenca na igraca tj. Main charactera
slava::EnemyController::EnemyController(CharacterPtr player) {
	this->player = player;
}

// Evo je genijalna control metoda
void slava::EnemyController::control(Character* enemy) {

	// Ako je karakter tj. enemy mrtav izlazi iz funkcije nista ne radi
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
	const int kvad = 20;
	if (x < xTarget - kvad ) {
		enemy->moveRight();
		enemy->stopLeft();
	}
	else if (x > xTarget + kvad) {
		enemy->moveLeft();
		enemy->stopRight();
	}
	else {
		enemy->stopLeft();
		enemy->stopRight();
	}

	if (y < yTarget -kvad ) {
		enemy->moveDown();
		enemy->stopUp();
	}
	else if (y > yTarget + kvad) {
		enemy->moveUp();
		enemy->stopDown();
	}
	else {
		enemy->stopUp();
		enemy->stopDown();
	}

	// racunamo udaljenost od targeta
	double dist = std::sqrt((x - xTarget) * (x - xTarget) + (y - yTarget)*(y - yTarget));

	// ako je manja od 20 pixela i nismo uskoro zadali udarac targetu, zadaj udarac targetu
	// odigraj animaciju udarca koja je indexirana na nuli za enemije
	// smanji health igracu
	// javi igracu da je udaren gotHit(true) true se stavlja ako je character main character, ako nije stavlja se false
	// pokreni enemija u random smjeru
	// restartuj sat koji mjeri vrijeme od zadnjeg udarca
	if (dist  <= 40 && !hit) {
		
		hit = true;
		enemy->playAnimation(0);
		this->player->getStats()->health -= 0.05;
		this->player->gotHit(true);
		enemy->moveRandom();
		clock1.restart();
	
	}

	// e sada provjeravamo da li je igrac udario nas, ako je udaljenost manja od 20 pixela i igrac je u attack modu
	// smanji enemiju health za neki faktor * igracev level
	// javi da je enemy udaren
	// provjeri da li je enemy ubijen i ako jeste dodaj igracu sp-a
	if (dist <= 20 && this->player->isAttack) {

		enemy->getStats()->health -= this->player->getStats()->level * 0.01;

		enemy->gotHit(false);

		if (enemy->isDead()) {
			this->player->getGameWorld()->getNotification()->play("You killed the mamojebac!");
			enemy->alive();
			enemy->getSprite()->setPosition(0, 0);
			this->player->getStats()->sp += 200;
		}
		/* sf::Thread th(&Character::gotHit, enemy);
		th.launch(); */
		// enemy->gotHit();
	}

	// std::cout << enemy->getStats()->health * 100 << std::endl;

}