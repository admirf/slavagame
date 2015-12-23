#include "Camera.h"
#include "HUD.h"
#include <iostream>
#include <SFML\Graphics.hpp>

#define ABS(x) x < 0? -x: x

slava::Camera::Camera(sf::Sprite* sprite) {
	center = sprite;
	offsetX = 0;
	offsetY = 0;
}

void slava::Camera::setOffset(int x, int y) {
	offsetX = x;
	originalX = x;
	originalY = y;
	offsetY = y;
}

void slava::Camera::bindHUD(HUD* hud) {
	this->hud = hud;
	hasHUD = true;
}

void slava::Camera::setAcceleration(int n) {
	acc = n;
}

void slava::Camera::update(sf::View& view) {

	int x = center->getPosition().x;
	int y = center->getPosition().y;

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

	view.setCenter(nX, nY);

	if (hasHUD) {
		hud->setPosition(nX - view.getSize().x/2, nY - view.getSize().y/2);
	}
}