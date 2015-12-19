#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <SFML\Graphics.hpp>
#include "HUD.h"

namespace slava
{

	class Camera
	{
	private:
		sf::Sprite* center;
		int offsetX;
		int originalX;
		int offsetY;
		int originalY;
		HUD* hud;
		bool hasHUD = false;
		int acc = 1;

	public:
		Camera(sf::Sprite*);
		void setOffset(int, int);
		void update(sf::View&);
		void bindHUD(HUD*);
		void setAcceleration(int);
	};

}

#endif