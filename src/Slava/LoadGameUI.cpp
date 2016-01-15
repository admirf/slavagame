

#include "LoadGameUI.h"
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include "GameWorld.h"


slava::LoadGameUI::LoadGameUI(sf::Font& font, std::string path) {
    std::string saveGameName="Save #0";
    for(int i = 0; i < slava::NUMSAVES; i ++){
        saveGameName[6]=char(i+1+'0');
        saveNames.push_back(sf::Text());
        saveNames[i].setFont(font);
        saveNames[i].setString(saveGameName);
        saveNames[i].setColor(sf::Color::Blue);
    }
    for(int i = 0; i < slava::NUMSAVES; i ++ ){
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

void slava::LoadGameUI::control(GameWorld* world) {
    //std::cout<<" STA JE SAD?";
	sf::RenderWindow* win = world->getWindow();
	auto coords = sf::Mouse::getPosition(*win);
	auto worldCoords = win->mapPixelToCoords(coords);

	int xM = worldCoords.x;
	int yM = worldCoords.y;

    for(int i=0;i<backShapes.size();i++){
        if(contains(backShapes[i],xM,yM)){
            backShapes[i].setFillColor(sf::Color(0, 0, 0, 130));
        }else{
            backShapes[i].setFillColor(sf::Color(0, 0, 0, 180));
        }
    }

	if (contains(backShape, xM, yM)) {
		backShape.setFillColor(sf::Color(0, 0, 0, 130));
	}
	else {
		backShape.setFillColor(sf::Color(0, 0, 0, 180));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for(int i=0;i<backShapes.size();i++) if(contains(backShapes[i],xM,yM)){
            if(world->getMainCharacter()->importCharStats("savegames.txt",i)){
                this->active=false;
                world->unpause();
            }
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
    		if (contains(backShape, xM, yM)) {
            this->active=false;
            world->getUI("mainMenuUI")->active=true;
            /*for(auto i:world->views){
                if(compareStr(i.first,"mainMenuUI")){i.second->active=true;std::cout<<"MAINMENUPRONADJEN\n";}
            }*/
		}
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            this->active=false;
            world->getUI("mainMenuUI")->active=true;
    }
}

void slava::LoadGameUI::draw(sf::RenderWindow& win) {

	int xC = win.getView().getCenter().x;
	int yC = win.getView().getCenter().y;

    for(int i = 0; i < slava::NUMSAVES; i ++){

        backShapes[i].setPosition(xC-12,yC-50*slava::NUMSAVES+i*50);
        saveNames[i].setPosition(xC-10,yC-50*slava::NUMSAVES+i*50);
    }
    backShape.setPosition(xC-12,yC);
    backText.setPosition(xC-10,yC);

    for(int i = 0; i < slava::NUMSAVES; i ++){
        win.draw(backShapes[i]);
        win.draw(saveNames[i]);
    }
    win.draw(backShape);
    win.draw(backText);
}
