
#include "ScoreboardUI.h"
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include "GameWorld.h"


slava::ScoreboardUI::ScoreboardUI(sf::Font& font, std::vector<std::string> &scores) {
    if(scores.size()<5)for(int i=0;i<5-scores.size();i++)scores.push_back(std::string("0"));
    std::sort(scores.begin(),scores.end(),customCompare);
    std::reverse(scores.begin(),scores.end());
    std::string tName="Player # ";

    for(int i =0; i < 5; i ++){
        tName[8]=char(i+1+'0');
        playerNames.push_back(sf::Text());
        playerNames[i].setFont(font);
        playerNames[i].setString(tName);
        playerNames[i].setColor(sf::Color::Blue);
    }
    for(int i = 0; i < 5; i ++){
            std::cout<<i;
        playerScores.push_back(sf::Text());
        playerScores[i].setFont(font);
        playerScores[i].setString(scores[i]);
        playerScores[i].setColor(sf::Color::Blue);
    }
    for(int i = 0; i < 5; i ++ ){
        backShapes.push_back(sf::RectangleShape());
        backShapes[i].setSize(sf::Vector2f(250, 50));
        backShapes[i].setFillColor(sf::Color(0, 0, 0, 180));
    }
    backText.setFont(font);
    backText.setString("Go back");
    backText.setColor(sf::Color::Blue);
    backShape.setSize(sf::Vector2f(250,50));
    backShape.setFillColor(sf::Color(0, 0, 0, 180));
}

void slava::ScoreboardUI::control(GameWorld* world) {
    std::cout<<"POKRENUT SCOREBOARD\n";
	sf::RenderWindow* win = world->getWindow();
	world->pause();
	auto coords = sf::Mouse::getPosition(*win);
	auto worldCoords = win->mapPixelToCoords(coords);

	int xM = worldCoords.x;
	int yM = worldCoords.y;

	if (contains(backShape, xM, yM)) {
		backShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		backShape.setFillColor(sf::Color(0, 0, 0, 180));
	}


	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		if (contains(backShape, xM, yM)) {
            this->active=false;
            world->getUI("mainMenuUI")->active=true;
            /*
            for(auto i:world->views){
                if(compareStr(i.first,"mainMenuUI"))i.second->active=true;
                std::cout<<"TU\n";
            }*/

		}
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            this->active=false;
            world->getUI("mainMenuUI")->active=true;
            /*
            for(auto i:world->views){
                if(compareStr(i.first,"mainMenuUI"))i.second->active=true;
            }*/
    }

}

void slava::ScoreboardUI::draw(sf::RenderWindow& win) {

	int xC = win.getView().getCenter().x;
	int yC = win.getView().getCenter().y;

    for(int i = 0; i < 5; i ++){
        backShapes[i].setPosition(xC-12,yC-250+i*50);
        playerNames[i].setPosition(xC-10,yC-250+i*50);
        playerScores[i].setPosition(xC+130,yC-250+i*50);
    }
    backShape.setPosition(xC-12,yC);
    backText.setPosition(xC-10,yC);

    for(int i = 0; i < 5; i ++){
        win.draw(backShapes[i]);
        win.draw(playerNames[i]);
        win.draw(playerScores[i]);
    }
    win.draw(backShape);
    win.draw(backText);
}
