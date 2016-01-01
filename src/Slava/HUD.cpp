#include "HUD.h"


slava::HUD::HUD(Stats* stats, FontPtr font) {
	this->stats = stats;
	this->font = font;

	health_text.setFont(*font);
	std::string s;
	s = "Health: " + slava::toString(static_cast<int>(stats->health * 100)) + "%";
	health_text.setString(s);
	health_text.setColor(sf::Color::Red);

	sp_text.setFont(*font);
	s = "SP: " + slava::toString(stats->sp);
	sp_text.setString(s);
	sp_text.setColor(sf::Color::Red);

	lvl_text.setFont(*font);
	s = "Level: " + slava::toString(stats->level);
	lvl_text.setString(s);
	lvl_text.setColor(sf::Color::Red);

}

void slava::HUD::setStats(Stats* stats) {
	this->stats = stats;
}

void slava::HUD::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void slava::HUD::draw(sf::RenderWindow& win) {

	std::string s;
	s = "Health: " + slava::toString(static_cast<int>(stats->health * 100)) + "%";
	health_text.setString(s);

	s = "SP: " + slava::toString(stats->sp);
	sp_text.setString(s);

	s = "Level: " + slava::toString(stats->level);
	lvl_text.setString(s);
	
	
	health_text.setPosition(x, y);
	sp_text.setPosition(x, y + 40);
	lvl_text.setPosition(x, y + 80);
	
	win.draw(health_text);
	win.draw(sp_text);
	win.draw(lvl_text);

	if (stats->hit) {
		sf::RectangleShape rect(win.getDefaultView().getSize());
		rect.setPosition(x, y);
		rect.setFillColor(sf::Color(255, 0, 0, 50));
		win.draw(rect);
	}
}