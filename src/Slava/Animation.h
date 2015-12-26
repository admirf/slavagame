#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

namespace slava
{
	class Character;

	/*
		Klasa za animacije, u vektoru drzimo reference tekstureatj. frame-ove za karakter neki
		onda imamo vremena, interval je vrijeme izmedju promjene tekstura
		lastTime je vrijeme koristeno za pracenje tj. vrijeme od zadnje promjene
		clock je pomagalo iz sfmla s kojim mjerimo vrijeme
		animated je referenca za karakter kojem cemo mijenjat teksture
		onda jos drzimo referencu originalne teksture karaktera i nju vratimo na kraju animacije,
		started, set, count, originalCount su varijable potrebne za provjeravanje da li 
		animacija traje i brojanje u kojem smo frame-u
		Uglavnom animacija ne koristi threadove nego ih simulira mjerenjem vremena
		sada kako se koristi. Napravite instancu, date vektor sa teksturama interval vremena
		postavite Karakter koji ce bit animiran i pozovete play metodu kada zelite da se pokrene
		KRUCIJALNO: morate u main loopu pozivat update metodu da bi se mjerilo vrijeme (posto se ne koristi pravi thread nego simulira)
 	*/

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