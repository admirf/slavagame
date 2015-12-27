#ifndef HUD_H
#define HUD_H

#include <SFML\Graphics.hpp>
#include "Utility.h"
#include "Stats.h"

namespace slava
{
	/*
	Klasa koja treba da crta odredjene informacije na prozor, te informacije ovise o Stats referenci koja bude proslijedjenja
	takodjer u konstruktoru potrebno proslijediti path do fonta koji se koristi za ispis na display
	Jednostavno napravljen HUD, za detalje kako radi pogledati HUD.cpp
	BITNO: HUD se uvijek treba koristit u kombinaciji sa kamerom, tj nakon sto se napravi treba njegovu referencu proslijedit
	kameri da bi se HUD crto na poziciji kamere
	*/

	typedef std::shared_ptr<sf::Font> FontPtr;

	class HUD
	{
	private:
		Stats* stats;
		FontPtr font;
		int x = 0, y = 0;

	public:
		HUD(Stats* s, FontPtr);
		void setStats(Stats* s);
		void draw(sf::RenderWindow&);
		void setPosition(int, int);
	};

}

#endif