#include "Animation.h"
#include <iostream>

slava::Animation::Animation(std::vector<std::shared_ptr<sf::Texture> >& frames, sf::Time time) {
	this->frames = frames;
	this->interval = time;
	originalCount = frames.size();
	count = 0;
}

void slava::Animation::setAnimated(Character* c) {
	this->animated = c;
	this->originalTexture = c->getTexture();
	set = true;
}

void slava::Animation::play() {
	// std::cout << "Triggered";
	if (!set) return;
	
	if (!started) {
		std::cout << "Triggered";
		started = true;
		this->animated->getSprite()->setTexture(*frames[0]);
		clock.restart();
		lastTime = clock.getElapsedTime();
		count = 0;
	}
}

std::vector<std::shared_ptr<sf::Texture> > slava::Animation::getTextures() {
	return frames;
}

void slava::Animation::update() {
	if (started) {
		if (clock.getElapsedTime() - lastTime > interval && count < originalCount) {
			this->animated->getSprite()->setTexture(*frames[count]);
			++count;
			clock.restart();
			lastTime = clock.getElapsedTime();
		}
		else if (count == originalCount) {
			started = false;
			this->animated->setTexture(originalTexture);
		}
	}
}
