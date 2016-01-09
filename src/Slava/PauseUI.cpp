#include "PauseUI.h"
#include "GameWorld.h"

slava::PauseUI::PauseUI(sf::Font& font) {
	resume.setFont(font);
	resume.setString("Resume");
	resume.setColor(sf::Color::Red);

	save.setFont(font);
	save.setString("Save");
	save.setColor(sf::Color::Red);

	quit.setFont(font);
	quit.setString("Quit");
	quit.setColor(sf::Color::Red);

	rShape.setSize(sf::Vector2f(100, 50));
	sShape.setSize(sf::Vector2f(100, 50));
	qShape.setSize(sf::Vector2f(100, 50));
	rShape.setFillColor(sf::Color(0, 0, 0, 180));
	sShape.setFillColor(sf::Color(0, 0, 0, 180));
	qShape.setFillColor(sf::Color(0, 0, 0, 180));
}

void slava::PauseUI::control(GameWorld* world) {
	sf::RenderWindow* win = world->getWindow();

	auto coords = sf::Mouse::getPosition(*win);
	auto worldCoords = win->mapPixelToCoords(coords);

	int xM = worldCoords.x;
	int yM = worldCoords.y;

	if (contains(rShape, xM, yM)) {
		rShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		rShape.setFillColor(sf::Color(0, 0, 0, 180));
	}
	if (contains(sShape, xM, yM)) {
		sShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		sShape.setFillColor(sf::Color(0, 0, 0, 180));
	}
	if (contains(qShape, xM, yM)) {
		qShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		qShape.setFillColor(sf::Color(0, 0, 0, 180));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (contains(rShape, xM, yM)) {
			this->active = false;
			world->unpause();
		}
		if (contains(sShape, xM, yM)) {

		}
		if (contains(qShape, xM, yM)) {
			world->quit();
		}
	}
}

void slava::PauseUI::draw(sf::RenderWindow& win) {
	int xC = win.getView().getCenter().x;
	int yC = win.getView().getCenter().y;

	resume.setPosition(xC - 10, yC - 50);
	save.setPosition(xC - 10, yC);
	quit.setPosition(xC - 10, yC + 50);

	rShape.setPosition(xC - 12, yC - 50);
	sShape.setPosition(xC - 12, yC);
	qShape.setPosition(xC - 12, yC + 50);

	win.draw(rShape);
	win.draw(sShape);
	win.draw(qShape);
	win.draw(resume);
	win.draw(save);
	win.draw(quit);
}