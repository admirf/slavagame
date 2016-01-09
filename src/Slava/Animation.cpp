#include "Character.h"
#include "Animation.h"

slava::Animation::Animation(const char* id, std::vector<TexturePtr>& frames, sf::Time time) {
	this->id = id;
	this->frames = frames;
	this->interval = time;
	originalCount = frames.size();
	count = 0;
}

const char* slava::Animation::getID() { return this->id; }

void slava::Animation::setAnimated(Character* c) {
	this->animated = c;
	this->originalTexture = c->getTexture();
	set = true;
}

void slava::Animation::play() {
	// std::cout << "Triggered";
	if (!set) return;
	
	if (!started) {
		started = true;
		this->animated->getSprite()->setTexture(*frames[0]);
		clock.restart();
		lastTime = clock.getElapsedTime();
		count = 0;
	}
}

std::vector<slava::TexturePtr> slava::Animation::getTextures() {
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
			this->animated->getSprite()->setTexture(*originalTexture);
		}
	}
}
