#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>

slava::Map::Map(const char* path, std::shared_ptr<sf::Texture> texture, MapSize ms, int blockSize) {
	this->blockSize = blockSize;
	this->texture = texture;
	int sizeY = ms.y;
	int sizeX = ms.x;

	this->map.resize(sizeY);
	std::ifstream mapa(path);

	array.setPrimitiveType(sf::Quads);
	array.resize(sizeY * sizeX * 4);

	for (int i = 0; i < sizeY; ++i) {

		this->map[i].resize(sizeX);

		for (int j = 0; j < sizeX; ++j) {
			char c;
			mapa >> c; // i ovo da dozivim da koristim nesto sto smo radili na intru za programiranje
			std::shared_ptr<Block> block;
			// block->setPosition(j * blockSize, i * blockSize);
			// std::cout << c << '\n';
			switch (c) {
			case '0':
				block = std::make_shared<Block>(slava::TileFactory::createTile0(), 0, blockSize, j * blockSize, i * blockSize);
				break;
			case '1':
				block = std::make_shared<Block>(slava::TileFactory::createTile1(), 1, blockSize, j * blockSize, i * blockSize);
				break;
			case 'a':
				block = std::make_shared<Block>(slava::TileFactory::createTileA(), 2, blockSize, j * blockSize, i * blockSize);
				break;
			case 'b':
				block = std::make_shared<Block>(slava::TileFactory::createTileB(), 3, blockSize, j * blockSize, i * blockSize);
				break;
			case 'c':
				block = std::make_shared<Block>(slava::TileFactory::createTileC(), 4, blockSize, j * blockSize, i * blockSize);
				break;
			case 'd':
				block = std::make_shared<Block>(slava::TileFactory::createTileD(), 5, blockSize, j * blockSize, i * blockSize);
				break;
			case 'e':
				block = std::make_shared<Block>(slava::TileFactory::createTileE(), 6, blockSize, j * blockSize, i * blockSize);
				break;
			case 'f':
				block = std::make_shared<Block>(slava::TileFactory::createTileF(), 7, blockSize, j * blockSize, i * blockSize);
				break;
			case 'g':
				block = std::make_shared<Block>(slava::TileFactory::createTileG(), 8, blockSize, j * blockSize, i * blockSize);
				break;
			case 'h':
				block = std::make_shared<Block>(slava::TileFactory::createTileH(), 9, blockSize, j * blockSize, i * blockSize);
				break;
			case 'i':
				block = std::make_shared<Block>(slava::TileFactory::createTileI(), 10, blockSize, j * blockSize, i * blockSize);
				break;
			default:
				block = std::make_shared<Block>(slava::TileFactory::createTile0(), 0, blockSize, j * blockSize, i * blockSize);

			}

			sf::VertexArray tmp = block->getVertexArray();

			int index = (i + j * sizeY) * 4;
			array[index] = tmp[0];
			array[index + 1] = tmp[1];
			array[index + 2] = tmp[2];
			array[index + 3] = tmp[3];

			this->map[i][j] = block;

		}

	}
	mapa.close();
}

void slava::Map::draw(sf::RenderWindow& win) {
	win.draw(array, texture.get());
	/* for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			map[i][j]->draw(win);
		}
	} */
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

std::shared_ptr<slava::Block> slava::Map::blockAt(int x, int y) {
	return this->map[y][x];
}