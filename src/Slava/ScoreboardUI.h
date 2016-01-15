
#ifndef __SCOREBOARD_UI_H
#define __SCOREBOARD_UI_H

#include "UI.h"
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

namespace slava
{
	class ScoreboardUI: public virtual UI
	{
	private:
		std::vector<sf::Text> playerNames;
		std::vector<sf::Text> playerScores;
		std::vector<sf::RectangleShape> backShapes;
        sf::Text backText;
        sf::RectangleShape backShape;
	public:
		ScoreboardUI(sf::Font&, std::vector<std::string>&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
