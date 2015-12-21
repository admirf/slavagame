#include "EnemyController.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

slava::EnemyController::EnemyController(std::shared_ptr<Character> player) {
	this->player = player;
}

void slava::EnemyController::control(Character* enemy) {

	if (enemy->isDead()) {
		return;
	}

	int xTarget = player->getSprite()->getPosition().x;
	int yTarget = player->getSprite()->getPosition().y;

	int x = enemy->getSprite()->getPosition().x;
	int y = enemy->getSprite()->getPosition().y;

	x += enemy->getSprite()->getGlobalBounds().width / 2;
	y += enemy->getSprite()->getGlobalBounds().height / 2;

	xTarget += player->getSprite()->getGlobalBounds().width / 2;
	yTarget += player->getSprite()->getGlobalBounds().height / 2;

	if (clock1.getElapsedTime() > sf::milliseconds(1000)) {
		hit = false;
		if (x < xTarget) {
			enemy->moveRight();
			enemy->stopLeft();
		}
		else if (x > xTarget) {
			enemy->moveLeft();
			enemy->stopRight();
		}
		else {
			enemy->stopLeft();
			enemy->stopRight();
		}

		if (y < yTarget) {
			enemy->moveDown();
			enemy->stopUp();
		}
		else if (y > yTarget) {
			enemy->moveUp();
			enemy->stopDown();
		}
		else {
			enemy->stopUp();
			enemy->stopDown();
		}
	}

	double dist = std::sqrt((x - xTarget) * (x - xTarget) + (y - yTarget)*(y - yTarget));
	if (dist  <= 20 && !hit) {
		
		hit = true;
		enemy->playAnimation(0);
		this->player->getStats()->health -= 0.05;
		this->player->gotHit(true);
		enemy->moveRandom();
		clock1.restart();
	
	}

	if (dist <= 20 && this->player->isAttack) {

		enemy->getStats()->health -= this->player->getStats()->level * 0.01;

		enemy->gotHit(false);

		if (enemy->isDead()) {
			this->player->getStats()->sp += 200;
		}
		/* sf::Thread th(&Character::gotHit, enemy);
		th.launch(); */
		// enemy->gotHit();
	}

	// std::cout << enemy->getStats()->health * 100 << std::endl;

}