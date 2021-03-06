#include "Map.h"
#include "Utility.h"
#include <fstream>
#include <string>
#include <queue>
#include <iostream>

const int INF = 1 << 29;
const int moveSize = 4;
const int moveX[4] = { 0,-1,1,0 };
const int moveY[4] = { 1,0,0,-1 };

slava::Map::Map(const char* path, TexturePtr texture, MapSize ms, int blockSize) {

	mapSize = ms;

	// templejti za tajlove, trenutno imamo tri vrste tile-ova i sada cemo napravit te tri instance i drzat njihove reference
	std::vector<std::shared_ptr<Tile>> tileTemplates;
	tileTemplates.push_back(slava::TileFactory::createRigidTile());
	tileTemplates.push_back(slava::TileFactory::createNonRigidTile());
	tileTemplates.push_back(slava::TileFactory::createNonWalkable());
	tileTemplates.push_back(slava::TileFactory::createWater());

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
	pathMatrix.resize(sizeY);
	secondLayer.setPrimitiveType(sf::Quads);

	for (int i = 0; i < sizeY; ++i) {

		this->map[i].resize(sizeX); 
		pathMatrix[i].resize(sizeX);
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
					else if (c == 'c') defaultIndex = 3;
					else if (blockable[c - 'a']) defaultIndex = 2;
					else defaultIndex = 0;
					tmp = getQuad(i - 'a', blockSize, posX, posY);
					break;
				}
			}

			// Sad posto napravimo posebno quad, koji je sam tipa VertexArray, moramo ga dodat u pseudomultidimenzionalni niz quadova
			if (!defaultIndex || defaultIndex == 3) {
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

bool slava::Map::isOutOfRange(int x, int y) {
	if (x < 0 || y < 0 || x >= this->mapSize.x || y >= this->mapSize.y) return true;
	return false;
}

slava::MapSize slava::Map::getSize() {
	return this->mapSize;
}

slava::Coordinate slava::Map::getNextFromTo(Coordinate from, Coordinate to) {
	//std::ofstream debugFile("pathdebug.txt");
	for (int i = 0; i<this->pathMatrix.size(); i++) std::fill(pathMatrix[i].begin(), pathMatrix[i].end(), INF);
	std::queue<Coordinate> toCheck;
	while (!toCheck.empty())toCheck.pop();
	this->pathMatrix[from.y][from.x] = 0;
	toCheck.push(from);
	int b = 0;
	Coordinate currentTile(0, 0);
	while (!toCheck.empty()) {
		currentTile = toCheck.front();
		toCheck.pop();
		for (int directionIter = 0; directionIter<moveSize; directionIter++) {
			b++;
			if (this->isOutOfRange(currentTile.x + moveX[directionIter], currentTile.y + moveY[directionIter]) == false) {
				if (this->pathMatrix[currentTile.y + moveY[directionIter]][currentTile.x + moveX[directionIter]] > this->pathMatrix[currentTile.y][currentTile.x] + 1) {
					if (this->tileAt(currentTile.x + moveX[directionIter], currentTile.y + moveY[directionIter])->isWalkable == true) {



						this->pathMatrix[currentTile.y + moveY[directionIter]][currentTile.x + moveX[directionIter]] = this->pathMatrix[currentTile.y][currentTile.x] + 1;
						toCheck.push(Coordinate(currentTile.x + moveX[directionIter], currentTile.y + moveY[directionIter]));
					}
				}
			}

		}
	}
	// std::cout << b << '\n';
	if (this->pathMatrix[to.y][to.x] == INF)return from;
	currentTile = to;
	Coordinate prevTile = to;
	int currentMin;
	int whereMin;
	//debugFile <<"===================="<<'\n';
	//debugFile << from.x << " " << from.y << " " << '\n';
	//debugFile << to.x << " " << to.y << " " << '\n';
	//debugFile << "koraci" << '\n';
	while (true) {
		if (this->pathMatrix[currentTile.y][currentTile.x] == 1) return currentTile;//{ debugFile.close(); return currentTile;}
		for (int directionIter = 0; directionIter<moveSize; directionIter++) {
			if (this->isOutOfRange(currentTile.x + moveX[directionIter], currentTile.y + moveY[directionIter]) == false) {
				if (this->pathMatrix[currentTile.y + moveY[directionIter]][currentTile.x + moveX[directionIter]] == this->pathMatrix[currentTile.y][currentTile.x] - 1) {
					whereMin = directionIter;
				}
			}
		}
		//debugFile<<currentTile.x << " " << currentTile.y << '\n';
		prevTile.x = currentTile.x;
		prevTile.y = currentTile.y;
		currentTile.x += moveX[whereMin];
		currentTile.y += moveY[whereMin];
	}
}