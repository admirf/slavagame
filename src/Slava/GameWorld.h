#ifndef __GAME_WORLD_H
#define __GAME_WORLD_H

#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Camera.h"
#include "Notification.h"
#include "HUD.h"
#include "Map.h"
#include "Trigger.h"
#include "UI.h"
#include "Inventory.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace slava
{
	typedef std::shared_ptr<GameWorld> GameWorldPtr;
	class UI;
	class GameWorld
	{
	private:
		sf::RenderWindow* window;
		CharacterPtr mainCharacter;
		std::unordered_map<const char*, CharacterPtr> characters;
		std::unordered_map<const char*, Trigger*> triggers;
		std::unordered_map<const char*, Animation*> animations;
        std::vector<std::string> randomJokes;
		std::unordered_map<const char*, std::shared_ptr<DialogNode> > dialogs;
		std::shared_ptr<DialogNode> currentDialog;
		std::vector<const char*> toBeRemoved;
		std::vector<const char*> triggersToBeRemoved;

		Items* items;

		Camera* camera;
		HUD* hud;
		Notification* notification;
		sf::View* customView;
		Map* map;
		bool isSet[5];
		bool finished = false;
		bool isPaused = false;

	public:
	    void loadRandomJokes(std::string);
	    std::string getRandomJoke();
	    std::unordered_map<std::string, UI*> views;
		GameWorld(sf::RenderWindow*, Map*);
		void addUI(UI*);
		UI* getUI(std::string);
		void setMainCharacter(CharacterPtr);
		void addCharacter(CharacterPtr);
		void addCharacters(std::vector<CharacterPtr>&);
		void removeCharacter(const char*);
		std::unordered_map<const char*, CharacterPtr> getCharacters();
		void addTrigger(Trigger*);
		void removeTrigger(const char*);
		CharacterPtr getMainCharacter();
		std::unordered_map<const char*, Trigger*> getTriggers();
		void addDialog(std::shared_ptr<DialogNode>, const char*);
		std::shared_ptr<DialogNode> getDialog(const char*);
		void addAnimation(Animation*);
		Animation* getAnimation(const char*);
		void setCurrentDialog(const char*);
		std::shared_ptr<DialogNode> getCurrentDialog();
		void setCamera(Camera*);
		Camera* getCamera();
		void setHUD(HUD*);
		void setNotification(Notification*);
		void setItems(Items*);
		void setView(sf::View*);
		Items* getItems();
		bool isAllSet();
		void update();
		bool isFinished();
		void finish();
		void quit();
		void restart();
		void pause();
		void unpause();
		sf::RenderWindow* getWindow();
		Notification* getNotification();
	};
}

#endif
