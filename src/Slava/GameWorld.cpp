#include "GameWorld.h"

slava::GameWorld::GameWorld(sf::RenderWindow* win, Map* mapa): window(win), map(mapa) {
	for (int i = 0; i < 5; ++i) isSet[i] = false;
}

void slava::GameWorld::setMainCharacter(CharacterPtr character) {
	mainCharacter = character;
	isSet[0] = true;
}

void slava::GameWorld::addCharacter(CharacterPtr character) {
	characters.push_back(character);
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


void slava::GameWorld::start() {
	if (!isAllSet()) return;

	while (window->isOpen())
	{
		// Postavljamo kameru
		camera->update(*customView);

		sf::Event event;
		
		// Updatujemo kontrolu i animacije za ostale karaktere
		for (auto chars : characters) {
			chars->control();
			for (int i = 0; i < chars->getNumberOfAnimations(); ++i)
				chars->updateAnimation(i);
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

			for (auto chars : characters) {
				chars->control();
				for (int i = 0; i < chars->getNumberOfAnimations(); ++i)
					chars->updateAnimation(i);
			}

		}

		mainCharacter->updateAnimation(0);
		
		// cistimo prozor prije crtanja
		window->clear();

		// prvo crtamo mapu
		map->draw(*window);

		// Crtamo ostale karaktere koji nisu mrtvi
		for (auto chars : characters) {
			if (!chars->isDead())
				chars->draw(*window);
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







