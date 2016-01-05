#ifndef __STATS_H
#define __STATS_H

namespace slava
{
	/*
	Klasa koja drzi podatke o characteru
	vecina podataka tipa healtha i toga trebaju bit doublovi od 0 do 1
	Iskreno ne znam sto sam napravio da je klasa sa public fieldovima, prije je bio struct, nemam ideje sto sam na klasu promijenio
	*/
	class Stats
	{
	public:
		double health;
		double acceleration;
		// level sistem revamped
		int level;
		int gold;
		double strength;
		double endurance;
		double mana;
		double limit;
		bool hit = false;
		int sp; // skill points
	};

}

#endif