#include "Character.h"
#include "Stats.h"
#include "GameWorld.h"
#include <ctime>
#include <cstdlib>
#include <memory>
#include <iostream>
#define MIN(a, b) a > b? b: a
#define MAX(a, b) a > b? a: b

slava::Character::~Character() {
	delete sprite;
	// delete texture;
	delete controller;
	delete stats;
	// Napomena: Ubuduce odma koristit smart pointere 
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

void slava::Character::setGameWorld(GameWorld* game) {
	this->world = game;
}

slava::GameWorld* slava::Character::getGameWorld() {
	return world;
}

void slava::Character::alive() {
	this->stats->health = 1;
}

const char* slava::Character::getID() {
	return this->id;
}

void slava::Character::init() {
	vX = 0;
	vY = 0;
	stats = new Stats;
	stats->acceleration = 0.5;
	stats->health = 1;
	stats->level = 1;
	stats->sp = 0;
	stats->limit = limit;
}

slava::Character::Character(const char* id) {
	this->id = id;
	sprite = new sf::Sprite();
	init();
	
}

slava::Character::Character(const char* id, sf::Texture* text) {
	this->id = id;
	sprite = new sf::Sprite();
	sprite->setTexture(*text);
	// originalColor = sprite->getColor();
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

void slava::Character::setTexture(TexturePtr text) {
	texture = text;
	sprite->setTexture(*texture);
	// originalColor = sprite->getColor();
}

slava::TexturePtr slava::Character::getTexture() {
	return texture;
}

void slava::Character::draw(sf::RenderWindow& win) {

	if (clock.getElapsedTime() > sf::milliseconds(500) && hit) {
		sprite->setColor(sf::Color::White);
		hit = false;
		this->getStats()->hit = false;
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

void slava::Character::moveRandom() {
	srand(static_cast<unsigned>(time(0)));
	int r = rand() % 4;

	switch (r) {
	case 0:
		this->moveLeft();
		break;
	case 1:
		this->moveRight();
		break;
	case 2:
		this->moveUp();
		break;
	case 3:
		this->moveDown();
		break;
	default:
		this->moveRandom();
	}
}

void slava::Character::moveRight() {
	vX = MIN(((vX > 0) ? vX : -vX) + stats->acceleration, stats->limit * stats->level);
}

void slava::Character::moveLeft() {
	vX = MAX(((vX > 0) ? -vX : vX) - stats->acceleration, -stats->limit * stats->level);
}

void slava::Character::moveDown() {
	vY = MIN(((vY > 0) ? vY : -vY) + stats->acceleration, stats->limit * stats->level);
}

void slava::Character::moveUp() {
	vY = MAX(((vY > 0) ? -vY : vY) - stats->acceleration, -stats->limit * stats->level);
}

void slava::Character::levelUp() {
	stats->level += 0.25;
}

/* Nadajmo se da nikad nece trebat

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
*/

bool slava::Character::isDead() {
	if (this->stats->health < 0) return true;
	return false;
}

void slava::Character::gotHit(bool isMainCharacter) {
	clock.restart();
	hit = true;
	if (!isMainCharacter) {
		sprite->setColor(sf::Color::Red);
	}
	else {
		this->getStats()->hit = true;
	}
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

slava::Position slava::Character::getPositionOnTile(int tileSize) {
	Position p;
	p.x = this->sprite->getPosition().x / tileSize;
	p.y = this->sprite->getPosition().y / tileSize;
	return p;
}

void slava::Character::setMap(Map* map) {
	mapIsSet = true;
	this->worldMap = map;
}

slava::Map* slava::Character::getMap() {
	return this->worldMap;
}

// Ovo nek stoji zasad mada je daleko netacno ne mogu se smarat vise veceras
bool slava::Character::isValidMovementPoint(double x, double y) {
	int j = ((int)x + this->sprite->getGlobalBounds().width/2 - 1) / worldMap->getTileSize();
    int i = (int)y / worldMap->getTileSize();
	// 
	int pixelLength = this->sprite->getGlobalBounds().height / worldMap->getTileSize();
	for (int k = i; k <= pixelLength + i; ++k) {
		if (j < 0 || k < 0 || j >= worldMap->getSize().x || k >= worldMap->getSize().y) return false;
		if (!worldMap->tileAt(j, k)->isWalkable) return false;
	}
	
	std::cout << j << ':' << i << ' ' << worldMap->tileAt(j, i)->isWalkable << '\n';
	return true;
}

int slava::Character::getNumberOfAnimations() {
	return animations.size();
}