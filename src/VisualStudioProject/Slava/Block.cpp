#include "Block.h"
#include "Utility.h"

slava::Block::Block(std::shared_ptr<Tile> tile, std::shared_ptr<sf::Texture> texture) {
	this->tile = tile;
	this->rect = new sf::Sprite();
	this->rect->setTexture(*texture);
}

void slava::Block::setPosition(int x, int y) {
	this->rect->setPosition(x, y);
}

std::shared_ptr<slava::Tile> slava::Block::getTile() {
	return this->tile;
}

void slava::Block::draw(sf::RenderWindow& win) {
	win.draw(*this->rect);
}

slava::Block::~Block() {
	delete rect;
}