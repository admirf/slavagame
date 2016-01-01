#include "SkillView.h"
#include "SFML\Graphics.hpp"
#include "GameWorld.h"
#include "Utility.h"

slava::SkillView::SkillView(sf::Font& font){
	strength.setFont(font);
	strength.setColor(sf::Color::Red);
	strength.setString(" Strength  ");
	sStrength.setFillColor(sf::Color(0, 0, 0, 180));

	mana.setFont(font);
	mana.setColor(sf::Color::Red);
	mana.setString("  Mana  ");
	sMana.setFillColor(sf::Color(0, 0, 0, 180));

	endurance.setFont(font);
	endurance.setColor(sf::Color::Red);
	endurance.setString("  Endurance ");
	sEndurance.setFillColor(sf::Color(0, 0, 0, 180));

	sStrength.setSize(sf::Vector2f(strength.getGlobalBounds().width, strength.getGlobalBounds().height + 10));
	sMana.setSize(sf::Vector2f(mana.getGlobalBounds().width, mana.getGlobalBounds().height + 11));
	sEndurance.setSize(sf::Vector2f(endurance.getGlobalBounds().width, endurance.getGlobalBounds().height + 11));
}

// Heeereeeee cooomeeees theee fiiiishhh!!!!
void slava::SkillView::control(GameWorld* world) {
	sf::RenderWindow* win = world->getWindow();

	auto coords = sf::Mouse::getPosition(*win);
	auto worldCoords = win->mapPixelToCoords(coords);

	int xM = worldCoords.x;
	int yM = worldCoords.y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		std::cout << "Mouse positions: " << xM << ' ' << yM << std::endl;
		std::cout << "sStrength bounds: " << sStrength.getPosition().x << ' ' << sStrength.getPosition().y << std::endl;

		if (contains(sStrength, xM, yM)) {
			world->getMainCharacter()->increaseSkill(STRENGTH);
			world->unpause();
			this->active = false;
			world->getNotification()->play("Strength increased.");
		}
		else if (contains(sMana, xM, yM)) {
			world->getMainCharacter()->increaseSkill(MANA);
			world->unpause();
			this->active = false;
			world->getNotification()->play("Mana increased.");
		}
		else if (contains(sEndurance, xM, yM)) {
			world->getMainCharacter()->increaseSkill(ENDURANCE);
			world->unpause();
			this->active = false;
			world->getNotification()->play("Endurance increased.");
		}

	}

	if (contains(sStrength, xM, yM)) {
		sStrength.setFillColor(sf::Color(0, 0, 0, 120));
	}
	else sStrength.setFillColor(sf::Color(0, 0, 0, 180));

	if (contains(sMana, xM, yM)) {
		sMana.setFillColor(sf::Color(0, 0, 0, 120));
	}
	else sMana.setFillColor(sf::Color(0, 0, 0, 180));

	if (contains(sEndurance, xM, yM)) {
		sEndurance.setFillColor(sf::Color(0, 0, 0, 120));
	}
	else sEndurance.setFillColor(sf::Color(0, 0, 0, 180));
}

void slava::SkillView::draw(sf::RenderWindow& win) {
	int xC = win.getView().getCenter().x;
	int yC = win.getView().getCenter().y;
	
	strength.setPosition(xC - 15.8 * 10, yC);
	mana.setPosition(xC - 4 * 10, yC);
	endurance.setPosition(xC + 6.1 * 10, yC);

	sStrength.setPosition(strength.getPosition());
	sMana.setPosition(mana.getPosition());
	sEndurance.setPosition(endurance.getPosition());

	win.draw(sStrength);
	win.draw(sMana);
	win.draw(sEndurance);
	win.draw(strength);
	win.draw(endurance);
	win.draw(mana);
}