#ifndef GAME_WORLD_H
#define GAME_WORLD_H
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Camera.h"
#include "Notification.h"
#include "HUD.h"
#include "Map.h"
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
		std::vector<const char*> toBeRemoved;
		Camera* camera;
		HUD* hud;
		Notification* notification;
		sf::View* customView;
		Map* map;
		bool isSet[5];

	public:
		GameWorld(sf::RenderWindow*, Map*);
		void setMainCharacter(CharacterPtr);
		void addCharacter(CharacterPtr);
		void removeCharacter(const char*);
		std::unordered_map<const char*, CharacterPtr> getCharacters();
		void setCamera(Camera*);
		void setHUD(HUD*);
		void setNotification(Notification*);
		void setView(sf::View*);
		bool isAllSet();
		void start();

		Notification* getNotification();
	};
}

#endif
