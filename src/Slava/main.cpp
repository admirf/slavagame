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
#include "SkillUI.h"
#include "NPC.h"
#include "Dialog.h"
#include "DialogUI.h"
#include "InventoryUI.h"
#include "PauseUI.h"
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

int counter = 3;
bool triNapadaTrigger(GameWorld* world) {
	if (world->getCharacters()["enemy1"]->isDead()) return true;
	else return false;
}

void triNapada(GameWorld* world) {
	if (counter < 3) {
		world->getCharacters()["enemy1"]->alive();
		world->getCharacters()["enemy1"]->getSprite()->setPosition(14 * BLOCK_SIZE, 15 * BLOCK_SIZE);
		++counter;
	}
}

void hackAround(GameWorld* world) {
	counter = 0;
}

void odjednom(GameWorld* world) {
	world->getCharacters()["enemy1"]->alive();
	world->getCharacters()["enemy2"]->alive();
	world->getCharacters()["enemy3"]->alive();
}

void samoJedan(GameWorld* world) {
	world->getCharacters()["enemy1"]->alive();
	world->getCharacters()["enemy1"]->getSprite()->setPosition(14 * BLOCK_SIZE, 15 * BLOCK_SIZE);
}


int main()
{
	srand(static_cast<unsigned>(time(0)));
	// Resursi
	auto txt = loadTexture("tileset1.png");
	auto font = loadFont("Marlboro.ttf");
	auto item_tileset = loadTexture("inventory_tile_set.png");

	// Prozor
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Slava");
	window.setFramerateLimit(60);
	// window.setKeyRepeatEnabled(true);

	// Mapa
	MapSize ms = getMapSize("mapa1.txt");
	Map map("mapa1.txt", txt, ms, BLOCK_SIZE);

	// kreacija svijeta, mora bit poslije mape i prozora, a prije charactera da bi mogli stavit u character referencu na game world
	GameWorld* world = new GameWorld(&window, &map);

	// Itemi igrice
	vector<ItemPtr> items_vector = {
		createItem("empy", EMPTY, 0, 0, 0, 0, 0),
		createItem("Sword of Recklesness", SWORD, 0, 0, 0.15, 0, 0),
		createItem("Sword of Holy Light", SWORD, 0, 0, 0.20, 0, 0),
		createItem("Sword of the Conqueror", SWORD, 0, 0, 0.25, 0, 0),
		createItem("Shield of Righteousnous", SHIELD, 0, 0.25, 0, 0, 0)
	};
	Items items(item_tileset, 128, items_vector);

	// Kraj igre trigger
	Trigger gameOverTrigger("drugi");
	gameOverTrigger.setRun(runGameOver);
	gameOverTrigger.setTrigger(gameOver);

	// Za ona tri napada jebena
	Trigger trigger("tri-napada");
	trigger.fireOnce = false;
	trigger.setTrigger(triNapadaTrigger);
	trigger.setRun(triNapada);

	// Main character
	auto character = make_shared<Character>("feha");
	character->setMap(&map);
	character->setTexture(loadTexture("Main-Character.png"));
	character->setBlockTexture(loadTexture("Main-Character-Block.png"));
	character->setController(new KeyController());
	character->getStats()->health = 1;
	character->getStats()->sp = 0;
	character->setGameWorld(world);
	character->getSprite()->setPosition(0, 1000);
	character->addItem(1);
	character->addItem(4);
	character->currentShield = items.getItem(4);
	character->currentWeapon = items.getItem(1);
	/*character->addItem(1);
	character->addItem(3, 5);*/
	// animacija udaranja
	vector<shared_ptr<sf::Texture>> textures;
	textures.push_back(loadTexture("Main-Character-Hit.png"));
	Animation anim("hit", textures, sf::milliseconds(180));
	character->addAnimation(anim);
	vector<TexturePtr> textures1;
	textures1.push_back(loadTexture("Main-Character-Mana.png"));
	Animation animMana("mana", textures1, sf::milliseconds(180));
	character->addAnimation(animMana);

	// Tri neprijatelja koja cemo stalno vrtit
	auto enemy1 = EnemyFactory::createBasicEnemy("enemy1", character, 200, 400);
	enemy1->setGameWorld(world);
	enemy1->setMap(&map);
	enemy1->getStats()->health = -1;

	auto enemy2 = EnemyFactory::createBasicEnemy("enemy2", character, 150, 400);
	enemy2->setGameWorld(world);
	enemy2->setMap(&map);
	enemy2->getStats()->health = -1;

	auto enemy3 = EnemyFactory::createBasicEnemy("enemy3", character, 250, 400);
	enemy3->setGameWorld(world);
	enemy3->setMap(&map);
	enemy3->getStats()->health = -1;

	// Tvrtko jebac
	auto tvrtko = make_shared<Character>("tvrtko");
	tvrtko->setMap(&map);
	tvrtko->setTexture(loadTexture("tvrtko.png"));
	tvrtko->setController(new NPC(character)); // NPC kontroller btw isto ko i EnemyController zahtjeva main karakter kao arg
	tvrtko->setGameWorld(world);
	tvrtko->getSprite()->setPosition(50 * BLOCK_SIZE, 65 * BLOCK_SIZE);


	auto dialogT1 = Dialog::createDialog();
	dialogT1->question = "Are you willing to battle for me?";
	dialogT1->answers = {
		"Yes my king, i pledge my loyalty!",
		"No!",
		"You are not my king!",
		"I owe my loyalty to no one!",
	};
	auto dialogT2 = Dialog::createDialog();
	dialogT2->question = "Excellent! I have a request to make, are\n you willing to listen";
	dialogT2->answers = {
		"Whatever you wish my Lord",
		"I can't do it now",
		"",
		""
	};
	Dialog::connect(dialogT1, 0, dialogT2);
	auto dialogT3 = Dialog::createDialog();
	dialogT3->question = "Go to the north-west fortress, and tell\n to the noble Ljubomir, that i want him to bolster our forces";
	dialogT3->answers = {
		"Yes my king!", "", "", ""
	};
	Dialog::connect(dialogT2, 0, dialogT3);


	// Plemic
	auto ljubomir = make_shared<Character>("ljubomir");
	ljubomir->setMap(&map);
	ljubomir->setTexture(loadTexture("plemic.png"));
	ljubomir->setController(new NPC(character));
	ljubomir->setGameWorld(world);
	ljubomir->getSprite()->setPosition(15 * BLOCK_SIZE, 15 * BLOCK_SIZE);

	auto dialogL1 = Dialog::createDialog();
	dialogL1->question = "What do you want with me?";
	dialogL1->answers = {
		"New king, king Tvrtko, seeks your alleigance!",
		"You must obey new king!",
		"I want to fight your champion!",
		"Join our alliance."
	};
	auto dialogL2 = Dialog::createDialog();
	dialogL2->question = "I accept, but only if you can defeat my champions!";
	dialogL2->answers = {
		"Bring it on!!!", "", "", ""
	};
	/*ovdje bi bilo super ako bi mogao napraviiti da krene fight, gdje ce biti 3 enemy-a i pojavljivat ce se jedan za drugim. Kad pobijedis jednog pojavi se durgi.*/
	Dialog::connect(dialogL1, 0, dialogL2);
	Dialog::connect(dialogL1, 3, dialogL2);
	Dialog::setAction(dialogL2, 0, hackAround);
	auto dialogL3 = Dialog::createDialog();
	dialogL3->question = "Know your place. Champions kill him!";
	dialogL3->answers = {
		"Hah, bring it on!", "", "", ""
	};
	/*ovdje bi bilo super ako bi mogao napraviiti da krene fight, gdje ce biti 3 enemy-a odjednom i gdje sva tri moraju ubiti*/
	Dialog::connect(dialogL1, 1, dialogL3);
	Dialog::setAction(dialogL3, 0, odjednom);
	auto dialogL4 = Dialog::createDialog();
	dialogL4->question = "Champion, attack!";
	dialogL4->answers = {
		"Bring it on!", "", "", ""
	};
	/*ovdje bi bilo super ako bi mogao napraviiti da krene fight, gdje ce se pojaviti samo jedan enemy kojeg treba ubiti. ovo mozemo reci da je ko neki training ground ili nesto za grindanje expirienca*/
	Dialog::connect(dialogL1, 2, dialogL4);
	Dialog::setAction(dialogL4, 0, samoJedan);


	// Skill UI
	auto skillView = make_shared<SkillUI>(*font);
	skillView->active = false;
	skillView->id = "skillUI";

	// Dialog UI
	auto dialogUI = make_shared<DialogUI>(*font);
	dialogUI->active = false;
	dialogUI->id = "dialogUI";

	// Inventory UI
	auto inventoryUI = make_shared<InventoryUI>(*font, items);
	inventoryUI->active = false;
	inventoryUI->id = "inventoryUI";

	// Pause UI
	auto pauseUI = make_shared<PauseUI>(*font);
	pauseUI->active = false;
	pauseUI->id = "pauseUI";
	
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
	world->addAnimation(&animMana);
	world->addCharacter(enemy1);
	world->addCharacter(enemy2);
	world->addCharacter(enemy3);
	world->addCharacter(tvrtko);
	world->addCharacter(ljubomir);
	world->setCamera(&cam);
	world->setHUD(&hud);
	world->addUI(skillView.get());
	world->addUI(dialogUI.get());
	world->addUI(inventoryUI.get());
	world->addUI(pauseUI.get());
	world->setNotification(&notification);
	world->setView(&customView);
	world->addDialog(dialogT1, "tvrtko"); // ime dialoga mora bit jednako imenu npc-a za koji je vezan
	world->addDialog(dialogL1, "ljubomir"); // ponavljam kljuc/ime dialoga mora bit jednako ID-u npc-a za koji zelite da izazove dialog
	world->setItems(&items);
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
					character->getSprite()->setPosition(0, 1000);
					enemy1->getStats()->health = -1;
					enemy2->getStats()->health = -1;
					enemy3->getStats()->health = -1;
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

	// delete skillView;
	delete world;
	

	return 0;
}