#ifndef __TRIGGER_H
#define __TRIGGER_H

namespace slava
{
	class GameWorld;
	class Trigger
	{
	private:
		bool (*isTriggered)(GameWorld*);
		void (*run)(GameWorld*);
		bool fired = false;
		const char* id;
		bool triggerSet = false;
		bool runSet = false;
	public:
		Trigger(const char*);
		void setTrigger(bool (*f)(GameWorld*));
		void setRun(void (*f)(GameWorld*));
		void check(GameWorld*);
		bool hasFired();
		const char* getID();
	};
}

#endif
