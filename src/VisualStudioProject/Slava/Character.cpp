#include "Character.h"
#include "Stats.h"
#include <memory>
#include <iostream>
#define MIN(a, b) a > b? b: a
#define MAX(a, b) a > b? a: b

slava::Character::~Character() {
	delete sprite;
	// delete texture;
	delete controller;
	delete stats;
	// Napomena: Ubuduce odma koristit smart pointere a ne kurcit ko kompleksas sa etfa sa rucnim oslobadjanjem
	/*for (auto& anim : animations) {
		for (int i = 0; i < anim.getTextures().size(); ++i) {
			if (anim.getTextures()[i] != NULL) {
				delete anim.getTextures()[i];
				anim.getTextures()[i] = NULL;
			}
		}
		// anim.getTextures().clear();
	}*/
}

void slava::Character::init() {
	vX = 0;
	vY = 0;
	stats = new Stats;
	stats->acceleration = 0.5;
	stats->health = 1;
	stats->level = 1;
	stats->sp = 0;
}

slava::Character::Character() {
	sprite = new sf::Sprite();
	init();
}

slava::Character::Character(sf::Texture* text) {
	sprite = new sf::Sprite();
	sprite->setTexture(*text);
	originalColor = sprite->getColor();
	init();
}

slava::Stats* slava::Character::getStats() {
	return stats;
}

sf::Sprite* slava::Character::getSprite() {
	return this->sprite;
}

void slava::Character::setStats(Stats* stats) {
	if (this->stats != NULL) {
		delete this->stats;
	}
	this->stats = stats;
}

void slava::Character::setController(IController* controller) {
	this->controller = controller;
}

void slava::Character::control() {
	controller->control(this);
}

void slava::Character::setTexture(std::shared_ptr<sf::Texture> text) {
	texture = text;
	sprite->setTexture(*texture);
	originalColor = sprite->getColor();
}

std::shared_ptr<sf::Texture> slava::Character::getTexture() {
	return texture;
}

void slava::Character::draw(sf::RenderWindow& win) {

	if (clock.getElapsedTime() > sf::milliseconds(500) && hit) {
		sprite->setColor(sf::Color::White);
		hit = false;
		// clock.restart();
	}
	/*
	else {
		sprite->setColor(originalColor);
		hit = false;
		// clock.restart();
	}*/

	sprite->move(static_cast<float>(vX), static_cast<float>(vY));
	win.draw(*sprite, getTransform());
}

void slava::Character::stopUp() {
	if (vY < 0) vY = 0;
}

void slava::Character::stopDown() {
	if (vY > 0) vY = 0;
}

void slava::Character::stopRight() {
	if (vX > 0) vX = 0;
}

void slava::Character::stopLeft() {
	if (vX < 0) vX = 0;
}

void slava::Character::moveRight() {
	vX = MIN(((vX > 0) ? vX : -vX) + stats->acceleration, limit * stats->level);
}

void slava::Character::moveLeft() {
	vX = MAX(((vX > 0) ? -vX : vX) - stats->acceleration, -limit * stats->level);
}

void slava::Character::moveDown() {
	vY = MIN(((vY > 0) ? vY : -vY) + stats->acceleration, limit * stats->level);
}

void slava::Character::moveUp() {
	vY = MAX(((vY > 0) ? -vY : vY) - stats->acceleration, -limit * stats->level);
}

void slava::Character::levelUp() {
	stats->level += 0.25;
}

void slava::Character::addCollidableCharacter(std::shared_ptr<Character> other) {
	otherCharacters.push_back(other);
}

bool slava::Character::collision(std::shared_ptr<Character> other) {
	if (this->sprite->getGlobalBounds().intersects(other->getSprite()->getGlobalBounds())) {
		return true;
	}
	return false;
}

bool slava::Character::notColliding() {
	for (auto others : otherCharacters) {
		if (this->collision(others)) return false;
	}
	return true;
}

void slava::Character::clearCollidableCharacters() {
	this->otherCharacters.clear();
}

bool slava::Character::isDead() {
	if (this->stats->health < 0) return true;
	return false;
}

void slava::Character::gotHit() {
	clock.restart();
	hit = true;
	sprite->setColor(sf::Color::Red);
	// lastTimeHit = clock.getElapsedTime();
}

void slava::Character::addAnimation(Animation& anim) {
	anim.setAnimated(this);
	this->animations.push_back(anim);
}

void slava::Character::playAnimation(int n) {
	if (n >= animations.size()) return;
	animations[n].play();
}

void slava::Character::updateAnimation(int n) {
	if (n >= animations.size()) return;
	animations[n].update();
}

std::shared_ptr<sf::Texture> slava::loadTexture(const char* path) {
	auto tx = std::make_shared<sf::Texture>();
	if (!tx->loadFromFile(path)) {
		return NULL;
	}
	// tx->loadFromFile(path);
	tx->setSmooth(true);

	return tx;
}