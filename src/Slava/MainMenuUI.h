
#ifndef __MAINMENU_UI_H
#define __MAINMENU_UI_H

#include "UI.h"
#include <SFML\Graphics.hpp>

namespace slava
{
	class MainMenuUI: public virtual UI
	{
	private:
		sf::Text newGame;
		sf::Text loadGame;
		sf::Text scoreboard;
		sf::Text quit;
		sf::RectangleShape ngShape;
		sf::RectangleShape lgShape;
		sf::RectangleShape scShape;
		sf::RectangleShape quShape;
	public:
		MainMenuUI(sf::Font&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
