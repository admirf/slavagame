#ifndef __TILE_FACTORY_H
#define __TILE_FACTORY_H

#include "Tile.h"
#include "Utility.h"
#include <memory>
#include <vector>
#include <string>
#include <sstream>

namespace slava
{
	typedef std::vector<std::shared_ptr<sf::Texture>> Textures;

	// Klasa za kreiranje instanci template-a Tile struktura, naravno formiraju se reference
	class TileFactory
	{
	public:
		
		static std::shared_ptr<Tile> createRigidTile() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = true;
			return tile0;
		}
		static std::shared_ptr<Tile> createNonWalkable() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = false;
			tile0->isRigid = true;
			return tile0;
		}
		static std::shared_ptr<Tile> createNonRigidTile() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		
	};
}

#endif