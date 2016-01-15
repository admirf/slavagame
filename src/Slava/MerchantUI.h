#ifndef __MERCHANT_UI_H
#define __MERCHANT_UI_H

#include "UI.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include "Inventory.h"

namespace slava
{
	class MerchantUI : virtual public UI
	{
	private:
		Items inven;
		std::vector<sf::RectangleShape> items;
		sf::RectangleShape use;
		sf::Text useText;
		sf::Text gold;
		int current = 0;
	public:
		MerchantUI(sf::Font&, Items&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif

