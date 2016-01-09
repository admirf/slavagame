#include "DialogUI.h"
#include "GameWorld.h"

slava::DialogUI::DialogUI(sf::Font& font) {
	question.setFont(font);
	question.setCharacterSize(24);
	question.setColor(sf::Color::Red);
	sQuestion.setFillColor(sf::Color(0, 0, 0, 180));
	sQuestion.setSize(sf::Vector2f(400, 70));
	for (int i = 0; i < 4; ++i) {
		answers[i].setFont(font);
		answers[i].setCharacterSize(24);
		answers[i].setColor(sf::Color::Red);
		sAnswers[i].setFillColor(sf::Color(0, 0, 0, 180));
		sAnswers[i].setSize(sf::Vector2f(400, 60));
	}
}

void slava::DialogUI::control(GameWorld* world) {
	if (!cpySet) {
		cpy = world->getCurrentDialog();
		cpySet = true;
	}

	sf::RenderWindow* win = world->getWindow();

	auto coords = sf::Mouse::getPosition(*win);
	auto worldCoords = win->mapPixelToCoords(coords);

	int xM = worldCoords.x;
	int yM = worldCoords.y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for (int i = 0; i < 4; ++i) {
			if (contains(sAnswers[i], xM, yM)) {

				if (cpy->action[i] != NULL) {
					cpy->action[i](world);
				}
				if (cpy->next[i] != NULL) {
					cpy = cpy->next[i];
				}
				else {
					cpySet = false;
					this->active = false;
					world->unpause();
				}
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (contains(sAnswers[i], xM, yM)) {
			sAnswers[i].setFillColor(sf::Color(0, 0, 0, 120));
		}
		else {
			sAnswers[i].setFillColor(sf::Color(0, 0, 0, 180));
		}
	}
}

void slava::DialogUI::draw(sf::RenderWindow& win) {
	int xC = win.getView().getCenter().x;
	int yC = win.getView().getCenter().y;

	if (cpy->question.length() > 40) {
		question.setCharacterSize(15);
	}
	else {
		question.setCharacterSize(24);
	}
	question.setString("  " + cpy->question);
	for (int i = 0; i < 4; ++i) {
		if (cpy->answers[i] != "") {
			answers[i].setString("  " + cpy->answers[i]);
		}
		else {
			answers[i].setString("  ...");
		}
		
		answers[i].setPosition(xC - 200, yC + 60 * i);
		sAnswers[i].setPosition(xC - 200, yC + 60 * i - 10);
		win.draw(sAnswers[i]);
		win.draw(answers[i]);
	}

	question.setPosition(xC - 200, yC - 60);
	sQuestion.setPosition(xC - 200, yC - 80);
	

	win.draw(sQuestion);
	win.draw(question);
}