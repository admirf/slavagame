#ifndef __MAP_H
#define __MAP_H

#include "Tile.h"
#include "TileFactory.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

namespace slava
{
	typedef std::shared_ptr<sf::Texture> TexturePtr;
	typedef std::vector<std::vector<std::shared_ptr<Tile> > > RawMap; // Nazalost ko ovo vidi nece nikad znat da sam ovo bio implementiro
																	   // sa smart pointerima na vektore i bilo je jako sexy, al srecom
																	   // sam se dosjetio da iako vector spasimo na stack da ce elementi bit
																	   // bit na heapu, tako da nema potrebe za
																	   // typedef std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Block>>>>> RawMap; koji sam bio koristio prije

	struct MapSize { int x; int y; };
	MapSize getMapSize(const char*);

	/*
	Klasa koja formira mapu igrice, zapravo formira dvije vrste niza, jedan pseudo 2d niz quadova koji se koristi za efikasno crtanje
	i 2d niz koji drzi reference na postojece tile template-e (3 zasad) koji koristimo da dobijemo informacije o tile-u na odredjenoj koordinati
	*/

	class Map
	{
	private:
		sf::VertexArray array;
		sf::VertexArray secondLayer;
		int blockSize;
		MapSize mapSize;
		RawMap map;
		TexturePtr texture;
	public:
		Map(const char*, TexturePtr, MapSize, int);
		bool isOutOfRange(int, int);
		void draw(sf::RenderWindow& win, bool isLayer=false);
		std::shared_ptr<Tile> tileAt(int, int);
		MapSize getSize();
		int getTileSize();
	};

}

#endif MAP_H