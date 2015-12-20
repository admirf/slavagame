#ifndef STATS_H
#define STATS_H

namespace slava
{

	class Stats
	{
	public:
		double health;
		double acceleration;
		// level ide po 0.25 napredak pa cemo mnozit sa nekim stvarima, lakse nego kompleksno levelovanje
		double level;
		int sp; // skill points
	};

}

#endif
