#include "Block.h"
#include "Utility.h"

slava::Block::Block(std::shared_ptr<Tile> tile, int textureIndex, int size, int x, int y) {
	this->tile = tile;
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);
	this->x = x;
	this->y = y;

	vertexArray[0].position = sf::Vector2f(x, y);
	vertexArray[1].position = sf::Vector2f(x + size, y);
	vertexArray[2].position = sf::Vector2f(x + size, y + size);
	vertexArray[3].position = sf::Vector2f(x, y + size);

	int n = textureIndex * size;
	vertexArray[0].texCoords = sf::Vector2f(n, 0);
	vertexArray[1].texCoords= sf::Vector2f(n + size, 0);
	vertexArray[2].texCoords = sf::Vector2f(n + size, size);
	vertexArray[3].texCoords = sf::Vector2f(n, size);
}


sf::VertexArray slava::Block::getVertexArray() {
	return this->vertexArray;
}

std::shared_ptr<slava::Tile> slava::Block::getTile() {
	return this->tile;
}
/* slava::Block::~Block() {
	delete rect;
} */