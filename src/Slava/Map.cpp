#include "Map.h"
#include "Utility.h"
#include <fstream>
#include <string>
#include <iostream>

slava::Map::Map(const char* path, TexturePtr texture, MapSize ms, int blockSize) {

	mapSize = ms;

	// templejti za tajlove, trenutno imamo tri vrste tile-ova i sada cemo napravit te tri instance i drzat njihove reference
	std::vector<std::shared_ptr<Tile>> tileTemplates;
	tileTemplates.push_back(slava::TileFactory::createRigidTile());
	tileTemplates.push_back(slava::TileFactory::createNonRigidTile());
	tileTemplates.push_back(slava::TileFactory::createNonWalkable());

	// non walkable tileovi
	std::ifstream blockf("blockable.txt");
	if (blockf.fail()) {
		std::cout << "Nema blockable.txt" << std::endl;
	}
	char tmp;
	bool blockable[30]{};
	while (blockf >> tmp) {
		blockable[tmp - 'a'] = true;
	}
	blockf.close();

	int defaultIndex = 0; // po default bacamo referencu na rigidTile u mapu

	this->blockSize = blockSize;
	this->texture = texture;
	int sizeY = ms.y;
	int sizeX = ms.x;

	this->map.resize(sizeY); // Ovo nam je reprezentabilna mapa sa kojom cemo imat informacije na kojoj poziciji je koja vrsta tajla od ona tri

	std::ifstream mapa(path); // ucitavamo mapu

	/*
	Posto crtat svaki rectangle ili crtat svaki sprite sa teksturom pojedinacni ubija performans
	Preso sam na formiranje mape putem VertexArray i sad imamo odgovarajuci performans
	Za verteks niz moram prvo svaki quad pojedinacno napravit i odredit koji dio teksture ga boji (switch-om provjeravamo)
	*/

	array.setPrimitiveType(sf::Quads);
	array.resize(sizeY * sizeX * 4);
	secondLayer.setPrimitiveType(sf::Quads);

	for (int i = 0; i < sizeY; ++i) {

		this->map[i].resize(sizeX); 

		for (int j = 0; j < sizeX; ++j) {
			char c;
			mapa >> c; // i ovo da dozivim da koristim nesto sto smo radili na intru za programiranje
			// std::shared_ptr<Block> block;

			sf::VertexArray tmp; // Pravimo rucno jedan quad

			int posX = j * blockSize;
			int posY = i * blockSize;

			// block->setPosition(j * blockSize, i * blockSize);
			// std::cout << c << '\n';

			tmp = getQuad(0, blockSize, posX, posY);

			// Switch mi treba da odredim koju teksturu da dam quadu i koju referencu na Tile iz tile templejta da spasim na j, i koordinatu mape
			for (int i = 'a'; i < 'z'; ++i) {
				if (c == i) {
					if (c == 'd') defaultIndex = 1;
					else if (blockable[c - 'a']) defaultIndex = 2;
					else defaultIndex = 0;
					tmp = getQuad(i - 'a', blockSize, posX, posY);
					break;
				}
			}

			// Sad posto napravimo posebno quad, koji je sam tipa VertexArray, moramo ga dodat u pseudomultidimenzionalni niz quadova
			if (!defaultIndex) {
				int index = (i + j * sizeY) * 4;
				array[index] = tmp[0];
				array[index + 1] = tmp[1];
				array[index + 2] = tmp[2];
				array[index + 3] = tmp[3];
			}
			else {
				secondLayer.append(tmp[0]);
				secondLayer.append(tmp[1]);
				secondLayer.append(tmp[2]);
				secondLayer.append(tmp[3]);
			}

			// spasavamo odgovarajucu referencu tile-a na poziciju da kasnije mozemo znat osobine tile-a na ovoj koordinati
			this->map[i][j] = tileTemplates[defaultIndex]; 
		}
		// std::cout << '\n';

	}
	mapa.close();
}

void slava::Map::draw(sf::RenderWindow& win, bool isLayer) {
	if(!isLayer) win.draw(array, texture.get());
	else win.draw(secondLayer, texture.get());
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

std::shared_ptr<slava::Tile> slava::Map::tileAt(int x, int y) {
	return this->map[y][x];
}

int slava::Map::getTileSize() {
	return blockSize;
}

slava::MapSize slava::Map::getSize() {
	return this->mapSize;
}