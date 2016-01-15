#include "GameWorld.h"
#include <fstream>
#include <ctime>
#include <cstdlib>

slava::GameWorld::GameWorld(sf::RenderWindow* win, Map* mapa): window(win), map(mapa) {
	for (int i = 0; i < 5; ++i) isSet[i] = false;
}

void slava::GameWorld::setMainCharacter(CharacterPtr character) {
	mainCharacter = character;
	isSet[0] = true;
}

void slava::GameWorld::addCharacter(CharacterPtr character) {
	characters.insert(std::make_pair(character->getID(), character));
	// characters[character->getID()] = character;
}

void slava::GameWorld::addCharacters(std::vector<CharacterPtr>& chars) {
	for (auto& character : chars) {
		characters[character->getID()] = character;
	}
}

void slava::GameWorld::removeCharacter(const char* id) {
	std::cout << "Gets called" << std::endl;
	toBeRemoved.push_back(id);
}

void slava::GameWorld::addTrigger(Trigger* t) {
	triggers[t->getID()] = t;
}

void slava::GameWorld::removeTrigger(const char* id) {
	triggersToBeRemoved.push_back(id);
}

std::unordered_map<const char*, slava::Trigger*> slava::GameWorld::getTriggers() {
	return triggers;
}

std::unordered_map<const char*, slava::CharacterPtr> slava::GameWorld::getCharacters() {
	return characters;
}

void slava::GameWorld::addAnimation(Animation* anim) {
	animations[anim->getID()] = anim;
}

slava::Animation* slava::GameWorld::getAnimation(const char* id) {
	return animations[id];
}

void slava::GameWorld::setCamera(Camera* cam) {
	camera = cam;
	isSet[1] = true;
}

void slava::GameWorld::setHUD(HUD* h) {
	hud = h;
	isSet[2] = true;
}

void slava::GameWorld::setNotification(Notification* notif) {
	notification = notif;
	isSet[3] = true;
}

bool slava::GameWorld::isAllSet() {
	for (int i = 0; i < 5; ++i) if (!isSet[i]) return false;
	return true;
}

void slava::GameWorld::setView(sf::View* view) {
	customView = view;
	isSet[4] = true;
}

slava::Notification* slava::GameWorld::getNotification() {
	return notification;
}

slava::CharacterPtr slava::GameWorld::getMainCharacter() {
	return mainCharacter;
}

bool slava::GameWorld::isFinished() { return finished; }
void slava::GameWorld::finish() { finished = true; }

void slava::GameWorld::restart() {
	this->notification->clear();
	this->mainCharacter->getStats()->health = 1;
	this->mainCharacter->getStats()->sp = 0;
	finished = false;
}

sf::RenderWindow* slava::GameWorld::getWindow() {
	return this->window;
}

void slava::GameWorld::addUI(UI* view) {
	views[view->id] = view;
}

slava::UI* slava::GameWorld::getUI(std::string id) {
	return views[id];
}

void slava::GameWorld::addDialog(std::shared_ptr<DialogNode> dialog, const char* key) {
	dialogs[key] = dialog;
}

std::shared_ptr<slava::DialogNode> slava::GameWorld::getDialog(const char* key) {
	return dialogs[key];
}

void slava::GameWorld::setCurrentDialog(const char* key) {
	currentDialog = dialogs[key];
}

void slava::GameWorld::loadRandomJokes(std::string path){
    std::ifstream inputFile(path);
    randomJokes.clear();
    std::string tmpStr;
    std::string toAdd;
    toAdd.clear();
    while(getline(inputFile,tmpStr)){
        while(true){
            getline(inputFile,tmpStr);
            if(tmpStr=="}")break;
            toAdd+=(tmpStr+"\n");
        }
        randomJokes.push_back(toAdd);
        toAdd.clear();
    }
    inputFile.close();
}

std::string slava::GameWorld::getRandomJoke(){
    std::srand(static_cast<unsigned int>(std::time(0)));
    return randomJokes[rand()%randomJokes.size()];
}

std::shared_ptr<slava::DialogNode> slava::GameWorld::getCurrentDialog() { return currentDialog; }

void slava::GameWorld::pause() { isPaused = true; }
void slava::GameWorld::unpause() { isPaused = false; }

void slava::GameWorld::setItems(Items* items) {
	this->items = items;
}

slava::Items* slava::GameWorld::getItems() {
	return items;
}

slava::Camera* slava::GameWorld::getCamera() {
	return this->camera;
}

void slava::GameWorld::quit() {
	window->close();
}

void slava::GameWorld::update() {
	if (!isAllSet()) return;
    //std::cout<<"ADRESA JE: "<<getUI("scoreboardUI")<<"\n";
	// Postavljamo kameru
	camera->update(*customView);

	sf::Event event;

	// Uklanjamo triggere koji su oznaceni za izbacivanje
	for (auto& id : triggersToBeRemoved) triggers.erase(id);
	triggersToBeRemoved.clear();

	// Provjeravamo sve triggere
	for (auto& trigger : triggers) {
		if (trigger.second->hasFired() && trigger.second->fireOnce) {
			triggersToBeRemoved.push_back(trigger.second->getID());
		}
		else {
			trigger.second->check(this);
		}
	}

	// Uklanjamo karaktere koji su oznaceni za izbacivanje
	for (auto& id : toBeRemoved) {
		characters.erase(id);
	}
	toBeRemoved.clear();

	// Updatujemo kontrolu i animacije za ostale karaktere
	for (auto& chars : characters) {
		if (!isPaused) {
			chars.second->control();
		}
		else {
			chars.second->stopMovement();
		}
		for (int i = 0; i < chars.second->getNumberOfAnimations(); ++i)
			chars.second->updateAnimation(i);
	}

	// Updatujemo kontrolu i animaciju za main karaktera
	if(!isPaused)
		mainCharacter->control();


	// Provjeravamo na evente
	while (window->pollEvent(event))
	{

		if (event.type == sf::Event::Closed)
			window->close();

		// Kontrola viewova, tj. UI elemenata
		for (auto& view : views) {
			if(view.second->active)
				view.second->control(this);
		}

		// Moramo kontrolu i animacije updateovat posebno u event stanju posto je posebna petlja
		if(!isPaused)
			mainCharacter->control();
		for (int i = 0; i < mainCharacter->getNumberOfAnimations(); ++i)
			mainCharacter->updateAnimation(i);

		for (auto& chars : characters) {
			if(!isPaused)
				chars.second->control();
			for (int i = 0; i < chars.second->getNumberOfAnimations(); ++i)
				chars.second->updateAnimation(i);
		}

	}

	mainCharacter->updateAnimation(0);

	// cistimo prozor prije crtanja
	window->clear();

	// prvo crtamo mapu
	map->draw(*window);

	// Crtamo ostale karaktere koji nisu mrtvi
	for (auto& chars : characters) {
		if (!chars.second->isDead())
			chars.second->draw(*window);
	}
	// crtamo nas karakter
	mainCharacter->draw(*window);

	// crtamo drugi layer mape ako postoji
	map->draw(*window, true);

	// crtamo HUD
	hud->draw(*window);

	// crtamo eventualne notifikacije
	notification->update(*window);

	// crtamo Viewove, ili ti ga UI elemente
	for (auto& view : views) {
		if(view.second->active)
			{view.second->draw(*this->window);}
	}

	// postavljamo prozor na nas view (zbog kamere)
	window->setView(*customView);
	// prikazujemo prozor
	window->display();


}







