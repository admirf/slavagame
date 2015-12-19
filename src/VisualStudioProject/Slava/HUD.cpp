#include "HUD.h"
#include "Utility.h"

slava::HUD::HUD(Stats* stats, const char* path) {
	this->stats = stats;
	this->font.loadFromFile(path);
}

void slava::HUD::setStats(Stats* stats) {
	this->stats = stats;
}

void slava::HUD::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void slava::HUD::draw(sf::RenderWindow& win) {
	sf::Text health_text;
	health_text.setFont(font);
	std::string s;
	s = "Health: " + slava::toString(static_cast<int>(stats->health * 100)) + "%";
	health_text.setString(s);
	health_text.setColor(sf::Color::Red);
	health_text.setPosition(x, y);

	sf::Text sp_text;
	sp_text.setFont(font);
	s = "SP: " + slava::toString(stats->sp);
	sp_text.setString(s);
	sp_text.setColor(sf::Color::Red);
	sp_text.setPosition(x, y + 40);
	
	win.draw(health_text);
	win.draw(sp_text);
}