#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>

slava::Map::Map(const char* path, slava::Textures texture, MapSize ms, int blockSize) {
	this->blockSize = blockSize;

	int sizeY = ms.y;
	int sizeX = ms.x;

	this->map.resize(sizeY);
	std::ifstream mapa(path);

	for (int i = 0; i < sizeY; ++i) {

		this->map[i].resize(sizeX);

		for (int j = 0; j < sizeX; ++j) {
			char c;
			mapa >> c; // i ovo da dozivim da koristim nesto sto smo radili na intru za programiranje
			std::shared_ptr<Block> block;
			// std::cout << c << '\n';
			switch (c) {
			case '0':
				block = std::make_shared<Block>(slava::TileFactory::createTile0(), texture[0]);
				break;
			case '1':
				block = std::make_shared<Block>(slava::TileFactory::createTile1(), texture[1]);
				break;
			case 'a':
				block = std::make_shared<Block>(slava::TileFactory::createTileA(), texture[2]);
				break;
			case 'b':
				block = std::make_shared<Block>(slava::TileFactory::createTileB(), texture[3]);
				break;
			case 'c':
				block = std::make_shared<Block>(slava::TileFactory::createTileC(), texture[4]);
				break;
			case 'd':
				block = std::make_shared<Block>(slava::TileFactory::createTileD(), texture[5]);
				break;
			case 'e':
				block = std::make_shared<Block>(slava::TileFactory::createTileE(), texture[6]);
				break;
			case 'f':
				block = std::make_shared<Block>(slava::TileFactory::createTileF(), texture[7]);
				break;
			case 'g':
				block = std::make_shared<Block>(slava::TileFactory::createTileG(), texture[8]);
				break;
			case 'h':
				block = std::make_shared<Block>(slava::TileFactory::createTileH(), texture[9]);
				break;
			case 'i':
				block = std::make_shared<Block>(slava::TileFactory::createTileI(), texture[10]);
				break;
			default:
				block = block = std::make_shared<Block>(slava::TileFactory::createTile0(), texture[0]);

			}

			block->setPosition(j * blockSize, i * blockSize);

			this->map[i][j] = block;

		}

	}
	mapa.close();
}

void slava::Map::draw(sf::RenderWindow& win) {
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			map[i][j]->draw(win);
		}
	}
}

slava::MapSize slava::getMapSize(const char* path) {


	std::ifstream mapa(path);

	if (mapa.fail()) {
		std::cout << "File not read!\n";
	}

	std::string s;
	int cnt = 0;

	while (std::getline(mapa, s)) {
		++cnt;
	}

	mapa.close();

	MapSize ms;
	ms.x = s.length();
	ms.y = cnt;

	std::cout << ms.x << ' ' << ms.y << '\n';
	return ms;
}