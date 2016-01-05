#ifndef __INVENTORY_UI_H
#define __INVENTORY_UI_H

#include "UI.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include "Inventory.h"

namespace slava
{
	class InventoryUI : virtual public UI
	{
	private:
		Items inven;
		std::vector<sf::RectangleShape> items;
		sf::Text itemName;
		sf::RectangleShape craftSlot1;
		sf::RectangleShape craftSlot2;
		sf::RectangleShape resultSlot;
		sf::RectangleShape use;
		sf::Text useText;
		sf::Text gold;
		int current = 0;
	public:
		InventoryUI(sf::Font&, Items&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
