#include "InventoryUI.h"
#include "GameWorld.h"

slava::InventoryUI::InventoryUI(sf::Font& font, Items& it) {
	inven = it;
	itemName.setFont(font);
	itemName.setColor(sf::Color::Blue);
	itemName.setString("");
	items.resize(10);
	for (int i = 0; i < 10; ++i) {
		items[i].setTexture(inven.getTileset().get());
		items[i].setSize(sf::Vector2f(inven.getItemSize(), inven.getItemSize()));
		items[i].setOutlineThickness(-10);
		items[i].setOutlineColor(sf::Color(0, 0, 0, 0));
	}
	use.setFillColor(sf::Color(0, 0, 0, 120));
	use.setSize(sf::Vector2f(120, 50));
	useText.setFont(font);
	useText.setColor(sf::Color::Blue);
	useText.setCharacterSize(34);
	useText.setString("Use");
	gold.setColor(sf::Color::Yellow);
	gold.setFont(font);
	gold.setString("");
}

void slava::InventoryUI::control(GameWorld* world) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		this->active = false;
		world->unpause();
		return;
	}

	sf::RenderWindow* win = world->getWindow();
	auto coords = sf::Mouse::getPosition(*win);
	auto worldCoords = win->mapPixelToCoords(coords);

	int xM = worldCoords.x;
	int yM = worldCoords.y;

	

	if (contains(use, xM, yM) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		use.setFillColor(sf::Color(0, 0, 0, 180));
	}
	else {
		use.setFillColor(sf::Color(0, 0, 0, 120));
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for (int i = 0; i < 10; ++i) {
			if (contains(items[i], xM, yM)) {
				items[current].setOutlineColor(sf::Color(0, 0, 0, 0));
				current = i;
				break;
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		for (int i = 0; i < 10; ++i) {
			if (contains(items[i], xM, yM)) {
				items[current].setOutlineColor(sf::Color(0, 0, 0, 0));
				current = i;
				world->getMainCharacter()->removeItem(i);
				break;
			}
		}

		if (contains(use, xM, yM)) {
			use.setFillColor(sf::Color(0, 0, 0, 120));
			int tmp = world->getMainCharacter()->getItem(current);
			ItemPtr it = world->getItems()->getItem(tmp);
			if (it->type == SWORD) {
				world->getMainCharacter()->currentWeapon = it;
			}
			else if (it->type == SHIELD) {
				world->getMainCharacter()->currentShield = it;
			}
			else {
				Stats* stats = world->getMainCharacter()->getStats();
				stats->endurance += it->enduranceEffect;
				stats->health = it->healthEffect;
				stats->mana += it->manaEffect;
				stats->strength += it->strengthEffect;
			}
		}
	}
	
	items[current].setOutlineColor(sf::Color(0, 0, 0, 180));
	int iType = world->getMainCharacter()->getItem(current);

	itemName.setString(world->getItems()->getItem(iType)->name);

	gold.setString("Gold: " + toString(world->getMainCharacter()->getStats()->gold));



	// Postavljanje pozicija i svega
	int xC = world->getWindow()->getView().getCenter().x;
	int yC = world->getWindow()->getView().getCenter().y;

	int half = world->getWindow()->getView().getSize().x / 3;

	xC -= half;
	yC -= inven.getItemSize();

	gold.setPosition(xC, yC - 40);

	for (int i = 0; i < 5; ++i) {
		items[i].setPosition(xC + inven.getItemSize() * i, yC);
		int l = world->getMainCharacter()->getItem(i) * inven.getItemSize();
		items[i].setTextureRect(
			sf::IntRect(l ,
			0 ,
			inven.getItemSize(),
			inven.getItemSize())
		);
	}

	yC += world->getItems()->getItemSize();

	for (int i = 5; i < 10; ++i) {
		items[i].setPosition(xC + inven.getItemSize() * (i - 5), yC);
		int l = world->getMainCharacter()->getItem(i) * inven.getItemSize();
		items[i].setTextureRect(
			sf::IntRect(l,
				0,
				inven.getItemSize(),
				inven.getItemSize())
			);
	}

	yC += world->getItems()->getItemSize() + 30;

	itemName.setPosition(xC, yC);

	int pX = xC + inven.getItemSize() * 4;
	use.setPosition(pX, yC);
	useText.setPosition(pX + 30, yC + 4.5);
	
	

}

void slava::InventoryUI::draw(sf::RenderWindow& win) {
	win.draw(itemName);
	win.draw(use);
	win.draw(useText);
	win.draw(gold);
	for (int i = 0; i < 10; ++i)
		win.draw(items[i]);
}