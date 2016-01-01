#ifndef __VIEW_H
#define __VIEW_H

#include <SFML\Graphics.hpp>

namespace slava
{
	class GameWorld;
	class View
	{
	public:
		bool active;
		const char* id;
		virtual void control(GameWorld*) = 0;
		virtual void draw(sf::RenderWindow&) = 0;
	};
}

#endif
