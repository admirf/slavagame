#ifndef CAMERA_H
#define CAMERA_H

#include "Map.h"

namespace sf
{
	class Sprite;
	class View;
}

namespace slava
{
	class HUD;
	class Notification;

	/*
	Kamera uzima sprite referencu kao argument (proslijedi se getSprite() karaktera) i ona prati onda taj sprite
	ostale opcije su da se stave offseti, tj da se tek nakon odredjenog predjenog puta karaktera kamera opet centrira na njeg
	takodjer je potrebno (ne znam vise jel potrebno ili nije) da se poveze kamera sa HUD-om (heads up display)
	da bi se HUD crto na poziciji kamere, moze se takodjer postavit ubrzanje kamere kada centrira na karakter
	Da bi kamera radila, posto je ona samo fancy wrapper za sf::View mora se u main loopu pozivat update(sf::View&)
	*/

	class Camera
	{
	private:
		MapSize ms;
		sf::Sprite* center;
		int offsetX;
		int originalX;
		int offsetY;
		int originalY;
		int tileSize;
		HUD* hud;
		Notification* notification;
		bool hasHUD = false;
		bool hasNotification = false;
		int acc = 1;

	public:
		Camera(sf::Sprite*, MapSize, int);
		void setOffset(int, int);
		void update(sf::View&);
		void bindHUD(HUD*);
		void bindNotification(Notification*);
		void setAcceleration(int);
	};

}

#endif