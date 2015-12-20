#ifndef HUD_H
#define HUD_H
#include "Stats.h"
#include <SFML\Graphics.hpp>

namespace slava
{

	class HUD
	{
	private:
		Stats* stats;
		sf::Font font;
		int x = 0, y = 0;

	public:
		HUD(Stats* s, const char*);
		void setStats(Stats* s);
		void draw(sf::RenderWindow&);
		void setPosition(int, int);
	};

}

#endif