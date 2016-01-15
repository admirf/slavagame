#include "Character.h"
#include "Stats.h"
#include "GameWorld.h"
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <memory>
#include <iostream>
#define MIN(a, b) a > b? b: a
#define MAX(a, b) a > b? a: b

slava::Position slava::Character::getPositionOnTile(int tileSize) {
	Position p;
	p.x = this->sprite->getPosition().x / tileSize;
	p.y = this->sprite->getPosition().y / tileSize;
	return p;
}

slava::Character::~Character() {
	delete sprite;
	delete controller;
	delete stats;
}

void slava::Character::setGameWorld(GameWorld* game) {
	this->world = game;
}

slava::GameWorld* slava::Character::getGameWorld() {
	return world;
}

void slava::Character::alive() {
	this->stats->health = 1;
}

const char* slava::Character::getID() {
	return this->id;
}

/**OPIS SAVEFILEA:
    game state ce se ucitavati u LoadGameUI, u sustini to su samo char stats, position na mapi
    i inventory
    exportCharStats uzima string path za datoteku koja sadrzi saveove i int saveIndex koji govori
    u koji save slot se spasava
    za sad ce imati 3 slota koja su fiksna
    opis saveFilea:
    3 slota

    opis slota:
    pocinje sa {
        bool empty
        double x double y
        stats
        inventory
    zavrsava sa }
*/


void slava::Character::exportCharStats(std::string path, int saveIndex){
    //std::pair<double,double> charPos= std::make_pair(get,vY);
    slava::Position charPos=this->getPositionOnTile(getMap()->getTileSize());
    slava::Stats* charStats=this->stats;
    std::vector<int> charInventory=this->inventory;
    std::ifstream inputFile(path);
    std::stringstream contentToExport;
    std::string thisLine;
    std::string junk;
    for(int i=0;i<slava::NUMSAVES;i++){
        if(i==saveIndex){
            getline(inputFile,thisLine); // ucitavanje { znaka
            contentToExport<<thisLine<<std::endl;
            while(junk!="}"){
                getline(inputFile,junk);
            }
            contentToExport<<0<<std::endl;
            contentToExport<<charPos.x<<" "<<charPos.y<<std::endl;
            contentToExport<<charStats->health<<std::endl;
            contentToExport<<charStats->mana_timer<<std::endl;
            contentToExport<<charStats->acceleration<<std::endl;
            contentToExport<<charStats->level<<std::endl;
            contentToExport<<charStats->gold<<std::endl;
            contentToExport<<charStats->strength<<std::endl;
            contentToExport<<charStats->endurance<<std::endl;
            contentToExport<<charStats->mana<<std::endl;
            contentToExport<<charStats->limit<<std::endl;
            contentToExport<<charStats->hit<<std::endl;
            contentToExport<<charStats->sp<<std::endl;
            contentToExport<<charInventory.size()<<std::endl;
            for(int inventI=0;inventI<charInventory.size();inventI++)
                contentToExport<<charInventory[inventI]<<std::endl;
            contentToExport<<"}"<<std::endl;
        }else{
            thisLine.clear();
            while(thisLine!="}"){
                getline(inputFile,thisLine); // ucitavanje { znaka
                contentToExport<<thisLine<<std::endl;
            }
        }
    }
    inputFile.close();
    std::ofstream outputFile(path);
    outputFile<<contentToExport.str()<<std::endl;
    outputFile.close();
    std::ofstream scoreboardOutputFile("scoreboard.txt",std::ofstream::app);
    scoreboardOutputFile<<charStats->sp<<std::endl;
    scoreboardOutputFile.close();
}

bool slava::Character::importCharStats(std::string path, int saveIndex){
    std::string temp;
    std::ifstream inputFile(path);
    bool emptySave;
    for(int i=0; i<slava::NUMSAVES;i++){
        if(i==saveIndex){
            std::cout<<i<<"\n";
            getline(inputFile,temp);
            inputFile>>emptySave;
            if(emptySave){inputFile.close();return false;}

            slava::Position charPos;
            slava::Stats charStats;
            inputFile>>charPos.x >> charPos.y;
            std::cout<<charPos.x<< " " << charPos.y<<"\n";
            getSprite()->setPosition(charPos.x*getMap()->getTileSize(),charPos.y*getMap()->getTileSize());
            inputFile>>charStats.health;
            inputFile>>charStats.mana_timer;
            inputFile>>charStats.acceleration;
            inputFile>>charStats.level;
            inputFile>>charStats.gold;
            inputFile>>charStats.strength;
            inputFile>>charStats.endurance;
            inputFile>>charStats.mana;
            inputFile>>charStats.limit;
            inputFile>>charStats.hit;
            inputFile>>charStats.sp;
            //std::cout<<"\n";
           // std::cout<<charStats.sp<<" "<<charStats.level<<"\n";
            setStats(&charStats);
            //std::cout<<charStats.sp<<" "<<charStats.level<<"\n";
            int charInvSize;
            inputFile>>charInvSize;
            inventory.resize(charInvSize);
            for(int inventI=0;inventI<charInvSize;inventI++)
                inputFile>>inventory[inventI];
        }else{
            temp.clear();
            while(temp!="}"){
                getline(inputFile,temp);
            }
        }
    }
    inputFile.close();
    return true;
}

void slava::Character::init() {
	vX = 0;
	vY = 0;
	stats = new Stats;
	stats->acceleration = 0.5;
	stats->health = 1;
	stats->level = 1;
	stats->endurance = 1;
	stats->strength = 1;
	stats->mana = 1;
	stats->mana_timer = 1;
	stats->limit = 2;
	stats->sp = 0;
	stats->gold = 0;
	inventory.resize(10);
	currentShield = createItem("", SHIELD, 0, 0, 0, 0, 0);
	currentWeapon = createItem("", SWORD, 0, 0, 0, 0, 0);
}

slava::Character::Character(const char* id) {
	this->id = id;
	sprite = new sf::Sprite();
	init();

}

slava::Character::Character(const char* id, sf::Texture* text) {
	this->id = id;
	sprite = new sf::Sprite();
	sprite->setTexture(*text);
	// originalColor = sprite->getColor();
	init();
}

slava::Stats* slava::Character::getStats() {
    //std::cout<<"VADIM STATS1 "<<stats->level << " " << stats->sp << "\n";
    //std::cout<<"VADIM STATS2 "<<stats->level << " " << stats->sp << "\n";
	return stats;
}

sf::Sprite* slava::Character::getSprite() {
	return this->sprite;
}

void slava::Character::setStats(Stats* _stats) {
	//if (this->stats != NULL) {
	//	delete this->stats;
	//}
	stats->acceleration=_stats->acceleration;
	stats->endurance=_stats->endurance;
	stats->gold=_stats->gold;
	stats->health=_stats->health;
	stats->hit=_stats->hit;
	stats->level=_stats->level;
	stats->limit=_stats->limit;
	stats->mana=_stats->mana;
	stats->mana_timer=_stats->mana_timer;
	stats->sp=_stats->sp;
	stats->strength=_stats->strength;
}

void slava::Character::setController(IController* controller) {
	this->controller = controller;
}

void slava::Character::control() {
	controller->control(this);
}

void slava::Character::setTexture(TexturePtr text) {
	texture = text;
	sprite->setTexture(*texture);
	blockTexture = text;
	// originalColor = sprite->getColor();
}

slava::TexturePtr slava::Character::getTexture() {
	return texture;
}

void slava::Character::draw(sf::RenderWindow& win) {

	if (clock.getElapsedTime() > sf::milliseconds(500) && hit) {
		sprite->setColor(sf::Color::White);
		hit = false;
		this->getStats()->hit = false;
		// clock.restart();
	}
	/*
	else {
	sprite->setColor(originalColor);
	hit = false;
	// clock.restart();
	}*/

	sprite->move(static_cast<float>(vX), static_cast<float>(vY));
	win.draw(*sprite, getTransform());
}

void slava::Character::stopUp() {
	if (vY < 0) vY = 0;
}

void slava::Character::stopDown() {
	if (vY > 0) vY = 0;
}

void slava::Character::stopRight() {
	if (vX > 0) vX = 0;
}

void slava::Character::stopLeft() {
	if (vX < 0) vX = 0;
}

void slava::Character::moveRandom() {
	srand(static_cast<unsigned>(time(0)));
	int r = rand() % 4;

	switch (r) {
	case 0:
		this->moveLeft();
		break;
	case 1:
		this->moveRight();
		break;
	case 2:
		this->moveUp();
		break;
	case 3:
		this->moveDown();
		break;
	default:
		this->moveRandom();
	}
}

void slava::Character::moveRight() {
	vX = MIN(((vX > 0) ? vX : -vX) + stats->acceleration, stats->limit * stats->endurance);
}

void slava::Character::moveLeft() {
	vX = MAX(((vX > 0) ? -vX : vX) - stats->acceleration, -stats->limit * stats->endurance);
}

void slava::Character::moveDown() {
	vY = MIN(((vY > 0) ? vY : -vY) + stats->acceleration, stats->limit * stats->endurance);
}

void slava::Character::moveUp() {
	vY = MAX(((vY > 0) ? -vY : vY) - stats->acceleration, -stats->limit * stats->endurance);
}

void slava::Character::levelUp() {
	++stats->level;
	hasLeveledUp = true;
}

void slava::Character::increaseSkill(skills skill) {
	switch (skill) {
	case STRENGTH:
		stats->strength += 0.15;
		break;
	case ENDURANCE:
		stats->endurance += 0.15;
		break;
	case MANA:
		stats->mana += 0.15;
		break;
	}
	hasLeveledUp = false;
}

bool slava::Character::canIncreaseSkill() {
	return hasLeveledUp;
}

void slava::Character::setDialog(std::shared_ptr<DialogNode>& node) {
	this->dialog = node;
}

std::shared_ptr<slava::DialogNode> slava::Character::getDialog() { return dialog; }

bool slava::Character::isDead() {
	if (this->stats->health < 0) return true;
	return false;
}

void slava::Character::gotHit(bool isMainCharacter) {
	clock.restart();
	hit = true;
	if (!isMainCharacter) {
		sprite->setColor(sf::Color::Red);
	}
	else {
		this->getStats()->hit = true;
	}
	// lastTimeHit = clock.getElapsedTime();
}

void slava::Character::addAnimation(Animation& anim) {
	anim.setAnimated(this);
	this->animations.push_back(anim);
}

void slava::Character::playAnimation(int n) {
	if (n >= animations.size()) return;
	animations[n].play();
}

void slava::Character::updateAnimation(int n) {
	if (n >= animations.size()) return;
	animations[n].update();
}



void slava::Character::setMap(Map* map) {
	mapIsSet = true;
	this->worldMap = map;
}

slava::Map* slava::Character::getMap() {
	return this->worldMap;
}

bool slava::Character::canBeHere(int x, int y) {
	x = x / worldMap->getTileSize();
	y = y / worldMap->getTileSize();

	if (worldMap->isOutOfRange(x, y)) return false;
	if (!worldMap->tileAt(x, y)->isWalkable) return false;

	return true;
}

bool slava::Character::isWalkableVertical(int x, int y, int z) {
	x = x / worldMap->getTileSize();
	y = y / worldMap->getTileSize();
	z = z / worldMap->getTileSize();

	if (worldMap->isOutOfRange(z, x) || worldMap->isOutOfRange(y, x)) return false;

	for (int i = y; i <= z; ++i) {
		if (!worldMap->tileAt(i, x)->isWalkable) return false;
	}

	return true;
}

bool slava::Character::isWalkableHorizontal(int x, int y, int z) {
	x = x / worldMap->getTileSize();
	y = y / worldMap->getTileSize();
	z = z / worldMap->getTileSize();

	if (worldMap->isOutOfRange(x, y) || worldMap->isOutOfRange(x, z)) return false;

	for (int i = y; i <= z; ++i) {
		if (!worldMap->tileAt(x, i)->isWalkable) return false;
	}

	return true;
}

bool slava::Character::canMoveUp() {
	int y = this->sprite->getPosition().y - 1;
	int x1 = this->sprite->getPosition().x;
	int x2 = x1 + this->sprite->getGlobalBounds().width - 1;

	return isWalkableVertical(y, x1, x2);
}

bool slava::Character::canMoveDown() {
	int y = this->sprite->getPosition().y + this->sprite->getGlobalBounds().height + 1;
	int x1 = this->sprite->getPosition().x;
	int x2 = x1 + this->sprite->getGlobalBounds().width - 1;

	return isWalkableVertical(y, x1, x2);
}

bool slava::Character::canMoveLeft() {
	int x = this->sprite->getPosition().x - 1;
	int y1 = this->sprite->getPosition().y;
	int y2 = y1 + this->sprite->getGlobalBounds().height - 1;

	return isWalkableHorizontal(x, y1, y2);
}

bool slava::Character::canMoveRight() {
	int x = this->sprite->getPosition().x + this->sprite->getGlobalBounds().width + 1;
	int y1 = this->sprite->getPosition().y;
	int y2 = y1 + this->sprite->getGlobalBounds().height - 1;

	return isWalkableHorizontal(x, y1, y2);
}

void slava::Character::addItem(int item, int index) {
	inventory[index] = item;
}

void slava::Character::addItem(int item) {
	for (int i = 0; i < inventory.size(); ++i) {
		if (!inventory[i]) {
			inventory[i] = item;
			std::cout<<"DODAJEM HP\n";
			return;
		}
	}
	inventory.push_back(item);
}

void slava::Character::removeItem(int index) {
	inventory[index] = 0;
}

int slava::Character::getItem(int index) {
	return inventory[index];
}

int slava::Character::getNumberOfAnimations() {
	return animations.size();
}

void slava::Character::setBlockTexture(TexturePtr texture) {
	blockTexture = texture;
}

void slava::Character::block() {
	if (!isBlock) {
		sprite->setTexture(*blockTexture);
		isBlock = true;
	}
}

void slava::Character::unblock() {
	if (isBlock) {
		sprite->setTexture(*texture);
		isBlock = false;
	}
}

void slava::Character::stopMovement() {
	stopDown();
	stopUp();
	stopLeft();
	stopRight();
}

bool slava::Character::canAddItem() {
    int cnt=0;
    for(int i=0;i<inventory.size();i++)if(inventory[i]==0)cnt++;
    return cnt>0;
}
