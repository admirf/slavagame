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
	if (world->getCharacters()["enemy1"]->isDead()) return true;
	else return false;
}

void exec(GameWorld* world) {
	diff += 0.05;
	auto enemy = world->getCharacters()["enemy1"];
	enemy->getStats()->health += diff;
	enemy->getStats()->limit += diff;
	enemy->getSprite()->setPosition(rand() % WIN_SIZE_X, rand() % WIN_SIZE_Y);
	enemy->alive();
}

void dialog1IncreaseInStrengthAction(GameWorld* world) {
	world->getMainCharacter()->increaseSkill(STRENGTH);
	world->getNotification()->play("Strength increased");
}


int main()
{
	srand(static_cast<unsigned>(time(0)));
	// Resursi
	auto txt = loadTexture("tileset1.png");
	auto font = loadFont("sgs.ttf");
	auto item_tileset = loadTexture("inventory_tile_set.png");

	// Prozor
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Slava");
	window.setVerticalSyncEnabled(true);
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
	character->getStats()->health = 1;
	character->getStats()->sp = 0;
	character->setGameWorld(world);
	character->getSprite()->setPosition(15 * BLOCK_SIZE, BLOCK_SIZE);
	character->addItem(1);
	character->addItem(3, 5);
	// animacija udaranja
	vector<shared_ptr<sf::Texture>> textures;
	textures.push_back(loadTexture("Main-Character-Hit.png"));
	Animation anim("hit", textures, sf::milliseconds(180));
	character->addAnimation(anim);

	// Neprijatelj
	auto enemy = EnemyFactory::createBasicEnemy("enemy1", character, 200, 400);
	enemy->setGameWorld(world);


	// Neki karakter koji ce imat konverzaciju, zvacemo ga Hamo
	auto hamo = make_shared<Character>("hamo");
	hamo->setMap(&map);
	hamo->setTexture(loadTexture("plemic.png"));
	hamo->setController(new NPC(character)); // NPC kontroller btw isto ko i EnemyController zahtjeva main karakter kao arg
	hamo->setGameWorld(world);
	hamo->getSprite()->setPosition(22 * BLOCK_SIZE, 10 * BLOCK_SIZE);

	// pravljenje dialoga, veliki tutorijal
	// Za one sto znaju sta rade kada ovo citaju, dialozi su stablo koje se rucno pravi
	auto dialog = Dialog::createDialog(); 
	// ovako napravimo pitanje
	dialog->question = "Are you a brave warrior?";
	// sad idu odgovori, uvijek ima cetiri odgovora, ako se odgovor ne popuni pisace ...
	// odgovori su indeksirani od 0 do 3 logicno al ja eto da slucajno neko glup cita
	dialog->answers[0] = "Brave huh? I am king of kings.";
	dialog->answers[1] = "Of course.";
	dialog->answers[2] = "Nah";
	dialog->answers[3] = "Do you want to test it.";
	// pravimo jos jedan dialog, ovdje pitanje stavimo odgovor npc-a i samo ostavimo prazne odgovore
	auto dialog2 = Dialog::createDialog();
	dialog2->question = "Then you shall have my sword";
	// Sada cemo povezati prva 3 odgovora iz pocetnog dialoga sa drugim dijalogom(koji ne vodi ni u sta)
	Dialog::connect(dialog, 0, dialog2);
	Dialog::connect(dialog, 1, dialog2);
	Dialog::connect(dialog, 2, dialog2);
	// pravimo jos neki dialog da istestiramo fino
	auto dialog3 = Dialog::createDialog();
	dialog3->question = "Do you wish to fight me. A legend of the\n    battlefield?";
	// naravno mogu se i ovako odgovori stavit ne mora se indeksirat, samo je bitno da ima cetiri odgovora
	dialog3->answers = { 
		"Let's fight!", 
		"It looks like I am not brave enough.", 
		"Of course. (Run away)", 
		"Sorry if I offended you." 
	};
	// neka do ovog dialoga dodje ako igrac odabere cetvti odgovor iz prvog
	Dialog::connect(dialog, 3, dialog3);
	// ovo je feature da kad se odredjeni odgovor odabere da se pokrene neka akcija
	// akcije su zapravo funkcija tipa void func(GameWorld*) njih proslijedjuemo kao treci argument, 
	// drugi argument je indeks odgovora u dialogu s kojim zelimo da povezemo akciju, akcije su tip
	// ako izaberes pravi odgovor ubacis characteru u inventory nesto (zasad nemamo inventory)
	Dialog::setAction(dialog3, 0, dialog1IncreaseInStrengthAction);
	// vezemo karakter i dijalog
	hamo->setDialog(dialog); // opcionalno bitno je da se doda u game world
	// dialog se mora posebno dodati i u game world

	// jos neki npc koji ce imat dialog, cisto da vidim radi li
	auto juka = make_shared<Character>("juka");
	juka->setMap(&map);
	juka->setTexture(loadTexture("sluga.png"));
	juka->setController(new NPC(character));
	juka->setGameWorld(world);
	juka->getSprite()->setPosition(35 * BLOCK_SIZE, 10 * BLOCK_SIZE);
	// E hajmo sad dialogcic
	auto jukaDialog = Dialog::createDialog();
	jukaDialog->question = "What are you called?";
	jukaDialog->answers = {"The Wolf", "The Dragon", "The Bear", "The Eagle"};
	auto jukaDialog2 = Dialog::createDialog();
	jukaDialog2->question = "Hmmm. Interesting. Now fuck off!";
	for (int i = 0; i < 4; ++i) Dialog::connect(jukaDialog, i, jukaDialog2);



	// Skill UI
	auto skillView = make_shared<SkillUI>(*font);
	skillView->active = false;
	skillView->id = "skillUI";

	// Dialog UI
	auto dialogUI = make_shared<DialogUI>(*font);
	dialogUI->active = false;
	dialogUI->id = "dialogUI";

	// Dialog UI
	auto inventoryUI = make_shared<InventoryUI>(*font, items);
	inventoryUI->active = false;
	inventoryUI->id = "inventoryUI";
	
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
	world->addCharacter(hamo);
	world->addCharacter(juka);
	world->setCamera(&cam);
	world->setHUD(&hud);
	world->addUI(skillView.get());
	world->addUI(dialogUI.get());
	world->addUI(inventoryUI.get());
	world->setNotification(&notification);
	world->setView(&customView);
	world->addDialog(jukaDialog, "juka"); // ime dialoga mora bit jednako imenu npc-a za koji je vezan
	world->addDialog(dialog, "hamo"); // ponavljam kljuc/ime dialoga mora bit jednako ID-u npc-a za koji zelite da izazove dialog
	world->setItems(&items);
	//world->addTrigger(&trigger);
	//world->addTrigger(&gameOverTrigger);

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

	// delete skillView;
	delete world;
	

	return 0;
}