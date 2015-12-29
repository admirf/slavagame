#include "Trigger.h"

slava::Trigger::Trigger(const char* id) {
	this->id = id;
}

void slava::Trigger::setTrigger(bool(*f)(GameWorld*)) {
	this->isTriggered = f;
	triggerSet = true;
}

void slava::Trigger::setRun(void(*f)(GameWorld*)) {
	this->run = f;
	runSet = true;
}

bool slava::Trigger::hasFired() { return fired; }

const char* slava::Trigger::getID() { return id; }

void slava::Trigger::check(GameWorld* world) {

	if (!triggerSet || !runSet) return;

	if (isTriggered(world)) {
		run(world);
	}
	fired = true;
}