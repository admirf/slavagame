#ifndef __SKILL_VIEW_H
#define __SKILL_VIEW_H

#include "View.h"
#include <memory>

namespace slava
{
	typedef std::shared_ptr<sf::Font> FontPtr;
	class SkillView: virtual public View
	{
	private:
		sf::Text strength;
		sf::Text mana;
		sf::Text endurance;
		sf::RectangleShape sStrength;
		sf::RectangleShape sMana;
		sf::RectangleShape sEndurance;
	public:
		SkillView(sf::Font&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
