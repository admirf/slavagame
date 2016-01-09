#include "Camera.h"
#include "HUD.h"
#include "Notification.h"
#include <iostream>
#include <SFML\Graphics.hpp>

#define ABS(x) x < 0? -x: x

slava::Camera::Camera(sf::Sprite* sprite, slava::MapSize ms, int tileSize) {
	this->tileSize = tileSize;
	center = sprite;
	offsetX = 0;
	offsetY = 0;
	this->ms = ms;
	this->ms.x = ms.x * tileSize;
	this->ms.y = ms.y * tileSize;
}

void slava::Camera::setOffset(int x, int y) {
	offsetX = x;
	originalX = x;
	originalY = y;
	offsetY = y;
}

slava::MapSize slava::Camera::getOffset() {
	return MapSize{ offsetX, offsetY };
}

void slava::Camera::bindHUD(HUD* hud) {
	this->hud = hud;
	hasHUD = true;
}

void slava::Camera::bindNotification(Notification* notification) {
	this->notification = notification;
	hasNotification = true;
}

void slava::Camera::setAcceleration(int n) {
	acc = n;
}

void slava::Camera::update(sf::View& view) {

	int x = center->getPosition().x;
	int y = center->getPosition().y;

	int width = view.getSize().x / 2;
	int height = view.getSize().y / 2;


	int nX = view.getCenter().x;
	int nY = view.getCenter().y;

	if (nX > x) {
		offsetX = originalX;
		if (nX - x > offsetX) {
			nX -= acc;
			offsetX += acc;
		}

	}
	if (nX < x) {
		offsetX = originalX;
		if (x - nX > offsetX) { 
			nX += acc; 
			offsetX -= acc;
		}
	}

	if (nY > y) {
		offsetY = originalY;
		if (nY - y > offsetY) {
			nY -= acc;
			offsetY += acc;
		}

	}
	if (nY < y) {
		offsetY = originalY;
		if (y - nY > offsetY) {
			nY += acc;
			offsetY -= acc;
		}
	}

	if (x + width - offsetX > ms.x) {
		nX = ms.x - width;
	}

	if (x - width + offsetX < 0) {
		nX = width;
	}

	if (y + height - offsetY > ms.y) {
		nY = ms.y - height;
	}

	if (y - height + offsetY < 0) {
		nY = height;
	}

	// std::cout << ms.x << ' ' << ms.y << "Ovo ti trenutno treba\n";

	view.setCenter(nX, nY);

	if (hasHUD) {
		hud->setPosition(nX - view.getSize().x/2, nY - view.getSize().y/2);
	}
	if (hasNotification) {
		// Ne pitajte me za logiku iza moje matematike
		notification->setPosition(view.getCenter().x - notification->getMessageWidth() * 5, view.getCenter().y + height/2 - height * 0.1);
	}
}