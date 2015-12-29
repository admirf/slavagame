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
#define BLOCK_SIZE 16

using namespace std;
using namespace slava;

double diff = 0;

bool gameOver(GameWorld* world) {
	if (world->getMainCharacter()->isDead()) return true;
	else return false;
}

void runGameOver(GameWorld* world) {
	world->finish();
}

bool sampleFunction(GameWorld* world) {
	if (world->getCharacters().empty()) return true;
	else return false;
}

void exec(GameWorld* world) {
	cout << "hahaha" << endl;
	diff += 0.10;
	auto enemy = EnemyFactory::createBasicEnemy("enemy", world->getMainCharacter(), rand() % WIN_SIZE_X, rand() % WIN_SIZE_Y);
	enemy->getStats()->health += diff;
	enemy->getStats()->limit += diff;
	world->getMainCharacter()->getStats()->limit += diff;
	enemy->addAnimation(*world->getAnimation("hit"));
	enemy->setGameWorld(world);
	world->addCharacter(enemy);
}


int main()
{
	srand(static_cast<unsigned>(time(0)));
	// Resursi
	auto txt = loadTexture("tileset1.png");
	auto font = loadFont("sgs.ttf");

	// Prozor
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Slava");
	window.setVerticalSyncEnabled(true);
	// window.setKeyRepeatEnabled(true);

	// Mapa
	MapSize ms = getMapSize("mapa1.txt");
	Map map("mapa1.txt", txt, ms, BLOCK_SIZE);

	// kreacija svijeta, mora bit poslije mape i prozora, a prije charactera da bi mogli stavit u character referencu na game world
	GameWorld* world = new GameWorld(&window, &map);

	// Trigger
	Trigger trigger("prvi");
	trigger.setRun(exec);
	trigger.setTrigger(sampleFunction);
	trigger.fireOnce = false;

	// Kraj igre trigger
	Trigger gameOverTrigger("drugi");
	gameOverTrigger.setRun(runGameOver);
	gameOverTrigger.setTrigger(gameOver);

	// Main character
	auto character = make_shared<Character>("feha");
	character->setMap(&map);
	character->setTexture(loadTexture("Main-Character.png"));
	character->setController(new KeyController());
	character->getStats()->health = 0.5;
	character->getStats()->sp = 0;
	character->setGameWorld(world);
	character->getSprite()->setPosition(15 * BLOCK_SIZE, BLOCK_SIZE);
	// animacija udaranja
	vector<shared_ptr<sf::Texture>> textures;
	textures.push_back(loadTexture("main_cha_hit.png"));
	Animation anim("hit", textures, sf::milliseconds(180));
	character->addAnimation(anim);

	// Neprijatelj
	auto enemy = EnemyFactory::createBasicEnemy("enemy1", character, 200, 400);
	enemy->addAnimation(anim);
	enemy->setGameWorld(world);

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
	world->addAnimation(&anim);
	world->addCharacter(enemy);
	world->setCamera(&cam);
	world->setHUD(&hud);
	world->setNotification(&notification);
	world->setView(&customView);
	world->addTrigger(&trigger);
	world->addTrigger(&gameOverTrigger);

	string over = "Game over. Press space to play again.";

	// Update-ujemo svijet, ovako imamo kontrolu mjenjat svijetove tj. levele ako nam je game loop izvan GameWorld klase
	// posto ce world bit level, treba provjeravat jel finished, ako jest crtamo taj svijet, ako nije saltamo na sljedeci bla bla bla
	while (window.isOpen()) {
		if (!world->isFinished()) {
			world->update();
		}
		else {

			sf::Event event;
			while (window.pollEvent(event)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					character->getSprite()->setPosition(15 * BLOCK_SIZE, BLOCK_SIZE);
					diff = 0;
					world->restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
			}

			window.clear();
			notification.setPosition(WIN_SIZE_X / 2 - BLOCK_SIZE * over.length() / 2, WIN_SIZE_Y/2);
			notification.play(over.c_str());
			notification.update(window);
			window.display();
		}
	}

	delete world;

	return 0;
}