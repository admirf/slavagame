#include <SFML/Graphics.hpp>
#include <memory>
#include "Character.h"
#include "KeyController.h"
#include "HUD.h"
#include "Camera.h"
#include "EnemyFactory.h"
#include "Utility.h"
#include "Map.h"
#include "TileFactory.h"
#include "Notification.h"
#include "GameWorld.h"
#include <iostream>
#define WIN_SIZE_X 1000
#define WIN_SIZE_Y 600

using namespace std;
using namespace slava;

bool sampleFunction(GameWorld* world) {
	if (world->getMainCharacter()->getSprite()->getPosition().x > 250) return true;
	else return false;
}

void exec(GameWorld* world) {
	world->getNotification()->play("Radi yeeeeaaaaah!!!!");
}

int main()
{
	// Resursi
	auto txt = loadTexture("tileset1.png");
	auto font = loadFont("sgs.ttf");

	// Prozor
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Slava");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(true);

	// Mapa
	MapSize ms = getMapSize("mapa1.txt");
	Map map("mapa1.txt", txt, ms, 16);

	// kreacija svijeta, mora bit poslije mape i prozora, a prije charactera da bi mogli stavit u character referencu na game world
	auto world = make_shared<GameWorld>(&window, &map);

	// Trigger
	Trigger trigger("prvi");
	trigger.setRun(exec);
	trigger.setTrigger(sampleFunction);

	// Main character
	auto character = make_shared<Character>("feha");
	character->setMap(&map);
	character->setTexture(loadTexture("Main-Character.png"));
	character->setController(new KeyController());
	character->getStats()->health = 0.5;
	character->getStats()->sp = 20000;
	character->setGameWorld(world);
	// animacija udaranja
	vector<shared_ptr<sf::Texture>> textures;
	textures.push_back(loadTexture("main_cha_hit.png"));
	Animation anim(textures, sf::milliseconds(180));
	character->addAnimation(anim);

	// Neprijatelj
	auto enemy = EnemyFactory::createBasicEnemy("enemy1", character, 200, 400);
	enemy->addAnimation(anim);
	enemy->setGameWorld(world);
	auto enemy2 = EnemyFactory::createBasicEnemy("enemy2", character, 200, 400);
	enemy2->addAnimation(anim);
	enemy2->setGameWorld(world);
	enemy2->getSprite()->setPosition(0, 500);

	// HUD, Notifikacije i Kamera
	HUD hud(character->getStats(), font);
	Notification notification(font, sf::Color::Red);
	Camera cam(character->getSprite(), ms, map.getTileSize());
	cam.setAcceleration(2);
	cam.setOffset(200, 100);
	sf::View customView(sf::FloatRect(0, 0, WIN_SIZE_X, WIN_SIZE_Y));
	cam.bindHUD(&hud);
	cam.bindNotification(&notification);

	// Spajamo sve u jedan svijet
	world->setMainCharacter(character);
	world->addCharacter(enemy);
	world->addCharacter(enemy2);
	world->setCamera(&cam);
	world->setHUD(&hud);
	world->setNotification(&notification);
	world->setView(&customView);
	world->addTrigger(&trigger);

	// Pokrecemo svijet
	world->start();

	return 0;
}