#ifndef GAME_WORLD_H
#define GAME_WORLD_H
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Camera.h"
#include "Notification.h"
#include "HUD.h"
#include "Map.h"
#include <vector>
#include <memory>

namespace slava 
{
	typedef std::shared_ptr<GameWorld> GameWorldPtr;
	class GameWorld
	{
	private:
		sf::RenderWindow* window;
		CharacterPtr mainCharacter;
		std::vector<CharacterPtr> characters;
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
