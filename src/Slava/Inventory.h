#ifndef __INVENTORY_H
#define __INVENTORY_H
#include <memory>
#include <vector>
#include <string>
#include "SFML\Graphics.hpp"

namespace slava {

	typedef std::shared_ptr<sf::Texture> TexturePtr;

	enum item_type {
		EMPTY,
		SWORD,
		SHIELD,
		POTION
	};

	struct Item {
		std::string name;
		item_type type;
		double healthEffect;
		double armorEffect;
		double strengthEffect;
		double manaEffect;
		double enduranceEffect;
	};

	typedef std::shared_ptr<Item> ItemPtr;

	static ItemPtr createItem(std::string name, item_type t, double h, double a, double s, double m, double e) {
		auto item = std::make_shared<Item>();
		item->name = name;
		item->type = t;
		item->healthEffect = h;
		item->armorEffect = a;
		item->strengthEffect = s;
		item->manaEffect = m;
		item->enduranceEffect = e;
		return item;
	}

	class Items
	{
	private:
		TexturePtr tileset;
		std::vector<ItemPtr> items;
		int itemSize;
	public:
		Items(TexturePtr t, int size, std::vector<ItemPtr>& v) : tileset(t), itemSize(size), items(v) {}
		Items() {};
		ItemPtr getItem(int index) { return items[index]; }
		TexturePtr getTileset() { return tileset; }
		int getItemSize() { return itemSize; }
	};

}

#endif
