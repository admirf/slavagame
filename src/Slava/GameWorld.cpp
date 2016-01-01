#include "GameWorld.h"

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

void slava::GameWorld::addView(View* view) {
	views[view->id] = view;
}

slava::View* slava::GameWorld::getView(const char* id) {
	return views[id];
}

void slava::GameWorld::pause() { isPaused = true; }
void slava::GameWorld::unpause() { isPaused = false; }

void slava::GameWorld::update() {
	if (!isAllSet()) return;

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
		if(!isPaused)
			chars.second->control();
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
		// if (!chars.second->isDead())
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
			view.second->draw(*this->window);
	}

	// postavljamo prozor na nas view (zbog kamere)
	window->setView(*customView);
	// prikazujemo prozor
	window->display();


}







