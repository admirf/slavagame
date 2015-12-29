#include "GameWorld.h"

slava::GameWorld::GameWorld(sf::RenderWindow* win, Map* mapa): window(win), map(mapa) {
	for (int i = 0; i < 5; ++i) isSet[i] = false;
}

void slava::GameWorld::setMainCharacter(CharacterPtr character) {
	mainCharacter = character;
	isSet[0] = true;
}

void slava::GameWorld::addCharacter(CharacterPtr character) {
	characters[character->getID()] = character;
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

void slava::GameWorld::start() {
	if (!isAllSet()) return;

	while (window->isOpen())
	{
		// Postavljamo kameru
		camera->update(*customView);

		sf::Event event;

		// Uklanjamo karaktere koji su oznaceni za izbacivanje
		for (auto& id : toBeRemoved) characters.erase(id);
		toBeRemoved.clear();

		// Uklanjamo triggere koji su oznaceni za izbacivanje
		for (auto& id : triggersToBeRemoved) triggers.erase(id);
		triggersToBeRemoved.clear();

		// Provjeravamo sve triggere
		for (auto& trigger : triggers) {
			trigger.second->check(this);
		}
		
		// Updatujemo kontrolu i animacije za ostale karaktere
		for (auto& chars : characters) {
			chars.second->control();
			for (int i = 0; i < chars.second->getNumberOfAnimations(); ++i)
				chars.second->updateAnimation(i);
		}

		// Updatujemo kontrolu i animaciju za main karaktera
		mainCharacter->control();
		

		// Provjeravamo na evente
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			// Moramo kontrolu i animacije updateovat posebno u event stanju posto je posebna petlja
			mainCharacter->control();
			for (int i = 0; i < mainCharacter->getNumberOfAnimations(); ++i)
				mainCharacter->updateAnimation(i);

			for (auto& chars : characters) {
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

		// postavljamo prozor na nas view (zbog kamere)
		window->setView(*customView);
		// prikazujemo prozor
		window->display();
	}


}







