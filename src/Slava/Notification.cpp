#include "Notification.h"
#include <string>

void slava::Notification::setValues(FontPtr font, sf::Color color) {
	this->color = color;
	this->font = font;
	this->isPlayed = false;
	this->duration = sf::milliseconds(1000);
}

slava::Notification::Notification(FontPtr font, sf::Color color) {
	setValues(font, color);
}

void slava::Notification::play(const char* msg) {
	if (isPlayed) return;

	this->message = msg;
	sf::Text text;
	text.setFont(*this->font);
	text.setColor(this->color);
	text.setCharacterSize(35);
	text.setString(message);
	text.setPosition(x, y);
	this->text = text;
	clock.restart();
	this->isPlayed = true;
}

void slava::Notification::play(std::string msg) {
	if (isPlayed) return;

	this->message = msg;
	sf::Text text;
	text.setFont(*this->font);
	text.setColor(this->color);
	text.setCharacterSize(35);
	text.setString(message);
	text.setPosition(x, y);
	this->text = text;
	clock.restart();
	this->isPlayed = true;
}

void slava::Notification::clear() {
	this->isPlayed = true;
	this->duration = sf::milliseconds(1000);
}

void slava::Notification::play(const char* msg, sf::Time duration) {
	play(msg);
	setDuration(duration);
}

void slava::Notification::play(std::string msg, sf::Time duration) {
	play(msg);
	setDuration(duration);
}

void slava::Notification::setPosition(int posX, int posY) {
    if (isPlayed) {
		x = posX;
		y = posY;
	}
}

void slava::Notification::setColor(sf::Color color) {
	this->color = color;
}

int slava::Notification::getMessageWidth() {
    int n;
    for(n = 0; message[n] != '\n' && n < message.length(); ++n);
	return n;
}

void slava::Notification::setDuration(sf::Time time) {
	duration = time;
}

void slava::Notification::update(sf::RenderWindow& win) {
	if (isPlayed) {
		if (clock.getElapsedTime() < duration) {
			// this->text.setColor(sf::Color(255, 0, 0, 255 * clock.getElapsedTime().asMilliseconds() / 100));
			this->text.setPosition(x, y);
			win.draw(text);
		}
		else {
			this->isPlayed = false;
		}
	}

}
