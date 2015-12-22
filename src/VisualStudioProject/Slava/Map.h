#ifndef MAP_H
#define MAP_H
#include "Block.h"
#include "TileFactory.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

namespace slava
{

	typedef std::vector<std::vector<std::shared_ptr<Block> > > RawMap; // Nazalost ko ovo vidi nece nikad znat da sam ovo bio implementiro
																	   // sa smart pointerima na vektore i bilo je jako sexy, al srecom
																	   // sam se dosjetio da iako vector spasimo na stack da ce elementi bit
																	   // bit na heapu, tako da nema potrebe za
																	   // typedef std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Block>>>>> RawMap; koji sam bio koristio prije

	struct MapSize { int x; int y; };
	MapSize getMapSize(const char*);

	class Map
	{
	private:
		int blockSize;
		RawMap map;
	public:
		Map(const char*, Textures, MapSize, int);
		void draw(sf::RenderWindow& win);
	};

}

#endif MAP_H