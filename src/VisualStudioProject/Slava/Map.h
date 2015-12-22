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
		sf::VertexArray array;
		int blockSize;
		RawMap map;
		std::shared_ptr<sf::Texture> texture;
	public:
		Map(const char*, std::shared_ptr<sf::Texture>, MapSize, int);
		void draw(sf::RenderWindow& win);
		std::shared_ptr<Block> blockAt(int, int);
	};

}

#endif MAP_H