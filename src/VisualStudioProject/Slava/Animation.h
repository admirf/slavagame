#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML\Graphics.hpp>
#include <vector>
#include "Character.h"
#include <memory>

namespace slava
{
	class Animation
	{
	private:
		std::vector<std::shared_ptr<sf::Texture> > frames;
		sf::Time interval;
		sf::Time lastTime;
		sf::Clock clock;
		Character* animated;
		std::shared_ptr<sf::Texture> originalTexture;
		bool started = false;
		bool set = false;
		int count;
		int originalCount;
	public:
		Animation(std::vector<std::shared_ptr<sf::Texture> >&, sf::Time);
		void setAnimated(Character*);
		void update();
		void play();
		std::vector<std::shared_ptr<sf::Texture> > getTextures();
	};
}

#endif
