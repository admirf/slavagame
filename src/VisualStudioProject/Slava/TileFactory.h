#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H
#include "Tile.h"
#include "Utility.h"
#include <memory>
#include <vector>
#include <string>
#include <sstream>

namespace slava
{
	typedef std::vector<std::shared_ptr<sf::Texture>> Textures;

	class TileFactory
	{
	public:
		/*
		static Textures getTileTextures() {
			Textures texts;
			texts.push_back(loadTexture("resources/myTiles/0.png"));
			texts.push_back(loadTexture("resources/myTiles/1.png"));

			for (int i = 'a'; i <= 'i'; ++i) {
				std::stringstream ss;
				ss << "resources/myTiles/";
				ss << static_cast<char>(i);
				ss << ".png";
				texts.push_back(loadTexture(ss.str().c_str()));
			}

			return texts;

		}*/

		static std::shared_ptr<Tile> createTile0() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = true;
			return tile0;
		}
		static std::shared_ptr<Tile> createTile1() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = true;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileA() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileB() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileC() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileD() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileE() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = false;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileF() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileG() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileH() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
		static std::shared_ptr<Tile> createTileI() {
			auto tile0 = std::make_shared<Tile>();
			tile0->isWalkable = true;
			tile0->isRigid = false;
			return tile0;
		}
	};
}

#endif