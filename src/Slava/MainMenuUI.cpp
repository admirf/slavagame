#include "MainMenuUI.h"
#include <algorithm>
#include <map>
#include <cstring>
#include "GameWorld.h"
#include "Utility.h"


slava::MainMenuUI::MainMenuUI(sf::Font& font) {
	newGame.setFont(font);
	newGame.setString("New Game");
	newGame.setColor(sf::Color::Red);

	loadGame.setFont(font);
	loadGame.setString("Load Game");
	loadGame.setColor(sf::Color::Red);

	scoreboard.setFont(font);
	scoreboard.setString("Scoreboard");
	scoreboard.setColor(sf::Color::Red);

	quit.setFont(font);
	quit.setString("Quit");
	quit.setColor(sf::Color::Red);

	ngShape.setSize(sf::Vector2f(200, 50));
    ngShape.setFillColor(sf::Color(0, 0, 0, 180));

    lgShape.setSize(sf::Vector2f(200, 50));
    lgShape.setFillColor(sf::Color(0, 0, 0, 180));

    scShape.setSize(sf::Vector2f(200, 50));
    scShape.setFillColor(sf::Color(0, 0, 0, 180));

    quShape.setSize(sf::Vector2f(200, 50));
    quShape.setFillColor(sf::Color(0, 0, 0, 180));
}

void slava::MainMenuUI::control(GameWorld* world) {
	sf::RenderWindow* win = world->getWindow();
	world->pause();
	auto coords = sf::Mouse::getPosition(*win);
	auto worldCoords = win->mapPixelToCoords(coords);

	int xM = worldCoords.x;
	int yM = worldCoords.y;

	if (contains(ngShape, xM, yM)) {
		ngShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		ngShape.setFillColor(sf::Color(0, 0, 0, 180));
	}
	if (contains(lgShape, xM, yM)) {
		lgShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		lgShape.setFillColor(sf::Color(0, 0, 0, 180));
	}
	if (contains(scShape, xM, yM)) {
		scShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		scShape.setFillColor(sf::Color(0, 0, 0, 180));
	}
	if (contains(quShape, xM, yM)) {
		quShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		quShape.setFillColor(sf::Color(0, 0, 0, 180));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (contains(ngShape, xM, yM)) {
			this->active = false;
			world->unpause();
		}
		if (contains(lgShape, xM, yM)) {
                //std::cout<<world->views["loadGameUI"];
            world->getUI("loadGameUI")->active=true;
            /*for(auto i:world->views){
                if(compareStr(i.first,"loadGameUI")){std::cout<<i.second;i.second->active=true;}
            }*/
            this->active=false;
		}
		if (contains(quShape, xM, yM)) {
			world->quit();
		}
		if (contains(scShape, xM, yM)) {
            world->getUI("scoreboardUI")->active=true;
            /*for(auto i:world->views){
                if(compareStr(i.first,"scoreboardUI")){i.second->active=true; std::cout<<"FOUND"<<'\n';}
            }*/
            this->active=false;
            world->unpause();

		}
	}
}

void slava::MainMenuUI::draw(sf::RenderWindow& win) {
	int xC = win.getView().getCenter().x;
	int yC = win.getView().getCenter().y;

	newGame.setPosition(xC - 10, yC - 100);
	loadGame.setPosition(xC - 10, yC-50);
	scoreboard.setPosition(xC - 10, yC);
	quit.setPosition(xC - 10, yC + 50);

	ngShape.setPosition(xC - 12, yC - 100);
	lgShape.setPosition(xC - 12, yC-50);
	scShape.setPosition(xC-12,yC);
	quShape.setPosition(xC - 12, yC + 50);

	win.draw(ngShape);
	win.draw(lgShape);
	win.draw(scShape);
	win.draw(quShape);
	win.draw(newGame);
	win.draw(loadGame);
	win.draw(scoreboard);
	win.draw(quit);
}
