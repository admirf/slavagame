#ifndef __NOTIFICATION_H
#define __NOTIFICATION_H

#include <SFML\Graphics.hpp>
#include <memory>
#include <string>

namespace slava
{
	typedef std::shared_ptr<sf::Font> FontPtr;

	class Notification
	{
	private:
		std::string message;
		FontPtr font;
		sf::Text text;
		sf::Color color;
		sf::Clock clock;
		int x = 0, y = 0;
		bool isPlayed = false;
		sf::Time duration;

		// static std::shared_ptr<Notification> instance;
	public:
		Notification(FontPtr, sf::Color);
		void play(const char*);
		void play(std::string);
		void play(const char*, sf::Time);
		void play(std::string, sf::Time);
		void setDuration(sf::Time);
		void update(sf::RenderWindow& win);
		int getMessageWidth();
		void setColor(sf::Color);
		void setPosition(int, int);
		void setValues(FontPtr, sf::Color);
		void clear();
	};
}

#endif
