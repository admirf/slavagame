#include "Character.h"
#define MIN(a, b) a > b? b: a
#define MAX(a, b) a > b? a: b

slava::Character::~Character() {
	delete sprite;
	delete texture;
	delete controller;
}

slava::Character::Character() {
	sprite = new sf::Sprite();
	vX = 0;
	vY = 0;
	level = 1;
}

slava::Character::Character(sf::Texture* text) {
	sprite = new sf::Sprite();
	sprite->setTexture(*text);
	vX = 0;
	vY = 0;
	level = 1;
}

void slava::Character::set_controller(IController* controller) {
	this->controller = controller;
}

void slava::Character::control() {
	controller->control(this);
}

void slava::Character::set_texture(sf::Texture* text) {
	texture = text;
	sprite->setTexture(*texture);
}

sf::Texture* slava::Character::get_texture() {
	return texture;
}

void slava::Character::draw(sf::RenderWindow& win) {
	sprite->move(static_cast<float>(vX), static_cast<float>(vY));
	win.draw(*sprite, getTransform());
}

void slava::Character::stop_up() {
	if (vY < 0) vY = 0;
}

void slava::Character::stop_down() {
	if (vY > 0) vY = 0;
}

void slava::Character::stop_right() {
	if (vX > 0) vX = 0;
}

void slava::Character::stop_left() {
	if (vX < 0) vX = 0;
}

void slava::Character::move_right() {
	vX = MIN(((vX > 0) ? vX : -vX) + acceleration, limit * level);
}

void slava::Character::move_left() {
	vX = MAX(((vX > 0) ? -vX : vX) - acceleration, -limit * level);
}

void slava::Character::move_down() {
	vY = MIN(((vY > 0) ? vY : -vY) + acceleration, limit * level);
}

void slava::Character::move_up() {
	vY = MAX(((vY > 0) ? -vY : vY) - acceleration, -limit * level);
}

void slava::Character::level_up() {
	level += 0.25;
}

sf::Texture* slava::load_texture(const char* path) {
	sf::Texture* tx = new sf::Texture();
	if (!tx->loadFromFile(path)) {
		return NULL;
	}
	// tx->loadFromFile(path);
	tx->setSmooth(true);

	return tx;
}