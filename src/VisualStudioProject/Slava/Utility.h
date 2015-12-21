#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sstream>
#include <memory>
#include <SFML\Graphics.hpp>

// Pomocne funkcije

namespace slava
{
	// Funkcija da brze ucitavamo teksture i vracamo reference, argument je path do fajla
	static std::shared_ptr<sf::Texture> loadTexture(const char* path) {
		auto tx = std::make_shared<sf::Texture>();
		if (!tx->loadFromFile(path)) {
			return NULL;
		}
		// tx->loadFromFile(path);
		tx->setSmooth(true);

		return tx;
	}

	// pretvaranje stvari u string
	template<typename T>
	std::string toString(T t) {
		std::stringstream ss;
		ss << t;
		std::string s;
		ss >> s;
		return s;
	}
}

#endif