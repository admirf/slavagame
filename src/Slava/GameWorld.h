#ifndef __GAME_WORLD_H
#define __GAME_WORLD_H

#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Camera.h"
#include "Notification.h"
#include "HUD.h"
#include "Map.h"
#include "Trigger.h"
#include "View.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace slava 
{
	typedef std::shared_ptr<GameWorld> GameWorldPtr;
	class GameWorld
	{
	private:
		sf::RenderWindow* window;
		CharacterPtr mainCharacter;
		std::unordered_map<const char*, CharacterPtr> characters;
		std::unordered_map<const char*, Trigger*> triggers;
		std::unordered_map<const char*, Animation*> animations;
		std::unordered_map<const char*, View*> views;
		std::vector<const char*> toBeRemoved;
		std::vector<const char*> triggersToBeRemoved;
		
		Camera* camera;
		HUD* hud;
		Notification* notification;
		sf::View* customView;
		Map* map;
		bool isSet[5];
		bool finished = false;
		bool isPaused = false;

	public:
		GameWorld(sf::RenderWindow*, Map*);
		void addView(View*);
		View* getView(const char*);
		void setMainCharacter(CharacterPtr);
		void addCharacter(CharacterPtr);
		void addCharacters(std::vector<CharacterPtr>&);
		void removeCharacter(const char*);
		std::unordered_map<const char*, CharacterPtr> getCharacters();
		void addTrigger(Trigger*);
		void removeTrigger(const char*);
		CharacterPtr getMainCharacter();
		std::unordered_map<const char*, Trigger*> getTriggers();
		void addAnimation(Animation*);
		Animation* getAnimation(const char*);
		void setCamera(Camera*);
		void setHUD(HUD*);
		void setNotification(Notification*);
		void setView(sf::View*);
		bool isAllSet();
		void update();
		bool isFinished();
		void finish();
		void restart();
		void pause();
		void unpause();
		sf::RenderWindow* getWindow();
		Notification* getNotification();
	};
}

#endif
