#ifndef __PAUSE_UI_H
#define __PAUSE_UI_H

#include "UI.h"
#include <SFML\Graphics.hpp>

namespace slava
{
	class PauseUI: public virtual UI
	{
	private:
		sf::Text resume;
		sf::Text save;
		sf::Text quit;
		sf::RectangleShape rShape;
		sf::RectangleShape sShape;
		sf::RectangleShape qShape;
	public:
		PauseUI(sf::Font&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
