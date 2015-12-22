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
		sf::Sprite* rect;
	public:
		Block(std::shared_ptr<Tile>, std::shared_ptr<sf::Texture>);
		~Block();
		std::shared_ptr<Tile> getTile();
		void setPosition(int, int);
		void draw(sf::RenderWindow&);
	};

}

#endif
