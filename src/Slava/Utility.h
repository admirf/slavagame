#ifndef __UTILITY_H
#define __UTILITY_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <iostream>
#include <cstring>
#include <SFML\Graphics.hpp>

// Pomocne funkcije

namespace slava
{
    const int NUMSAVES=3;
	typedef std::shared_ptr<sf::Font> FontPtr;
	typedef std::shared_ptr<sf::Texture> TexturePtr;
    static bool customCompare(const std::string &a, const std::string &b){
        if(a.size()!=b.size()) return a.size()<b.size();
        for(int i=0; i<a.size();i++){
            if(a[i]!=b[i])return a[i]<b[i];
        }
        return true;
    }
	// Check if coordinates are in rectangle
	static bool contains(sf::RectangleShape& shape, int x, int y) {
		return shape.getGlobalBounds().contains(sf::Vector2f(x, y));
	}
    static bool compareStr(const char *a, const char *b){
        int len=std::min(strlen(a),strlen(b));
        for(int i = 0; i < len; i ++) if(a[i]!=b[i])return false;
        return true;
    }
	// Pomocna funkcija za brzo formiranje quada u mapi
	static sf::VertexArray getQuad(int textureIndex, int size, int x, int y) {

		sf::VertexArray vertexArray(sf::Quads, 4);

		vertexArray[0].position = sf::Vector2f(x, y);
		vertexArray[1].position = sf::Vector2f(x + size, y);
		vertexArray[2].position = sf::Vector2f(x + size, y + size);
		vertexArray[3].position = sf::Vector2f(x, y + size);

		int n = textureIndex * size;
		vertexArray[0].texCoords = sf::Vector2f(n, 0);
		vertexArray[1].texCoords = sf::Vector2f(n + size, 0);
		vertexArray[2].texCoords = sf::Vector2f(n + size, size);
		vertexArray[3].texCoords = sf::Vector2f(n, size);

		return vertexArray;
	}

	// Funkcija da brze ucitavamo teksture i vracamo reference, argument je path do fajla
	static TexturePtr loadTexture(const char* path) {
		auto tx = std::make_shared<sf::Texture>();
		if (!tx->loadFromFile(path)) {
			std::cout << path << " not found\n";
			// tx->loadFromFile("0.png");
		}
		// tx->loadFromFile(path);
		tx->setSmooth(true);

		return tx;
	}

	// Funkcija da brze ucitavamo fontovge i vracamo reference, argument je path do fajla
	static FontPtr loadFont(const char* path) {
		auto tx = std::make_shared<sf::Font>();
		if (!tx->loadFromFile(path)) {
			std::cout << path << " not found\n";
			// tx->loadFromFile("0.png");
		}

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
