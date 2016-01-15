
#ifndef __SAVEGAME_UI_H
#define __SAVEGAME_UI_H

#include "UI.h"
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

namespace slava
{
	class SaveGameUI: public virtual UI
	{
	private:
		std::vector<sf::Text> saveNames;
		std::vector<sf::RectangleShape> backShapes;
        sf::Text backText;
        sf::RectangleShape backShape;
	public:
		SaveGameUI(sf::Font&, std::string);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
