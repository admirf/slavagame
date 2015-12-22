#ifndef BLOCK_H
#define BLOCK_H
#include "Tile.h"
#include <SFML\Graphics.hpp>
#include <memory>

namespace slava
{

	class Block
	{
	private:
		std::shared_ptr<Tile> tile;
		sf::VertexArray vertexArray;
		int x, y;
	public:
		Block(std::shared_ptr<Tile>, int, int, int, int);
		// ~Block();
		std::shared_ptr<Tile> getTile();
		sf::VertexArray getVertexArray();
	};

}

#endif
