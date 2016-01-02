#ifndef __SKILL_VIEW_H
#define __SKILL_VIEW_H

#include "UI.h"
#include <memory>

namespace slava
{
	typedef std::shared_ptr<sf::Font> FontPtr;
	class SkillUI: virtual public UI
	{
	private:
		sf::Text strength;
		sf::Text mana;
		sf::Text endurance;
		sf::RectangleShape sStrength;
		sf::RectangleShape sMana;
		sf::RectangleShape sEndurance;
	public:
		SkillUI(sf::Font&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
