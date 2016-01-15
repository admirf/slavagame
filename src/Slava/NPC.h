#ifndef __NPC_H
#define __NPC_H

#include "IController.h"
#include "Character.h"

namespace slava
{
	class NPC : virtual public IController
	{
	private:
		CharacterPtr player;
	public:
	    bool isEasterEgg=false;
		NPC(CharacterPtr play) : player(play) {}
		NPC(CharacterPtr play,bool easter) : player(play) {isEasterEgg=easter;}
		void control(Character* npc) {

			int dist = sqrt(pow(player->getSprite()->getPosition().x - npc->getSprite()->getPosition().x, 2)
				+ pow(player->getSprite()->getPosition().y - npc->getSprite()->getPosition().y, 2) );

			if (dist < 40 && !isEasterEgg) {
				npc->getGameWorld()->getNotification()->play("Press f to talk.");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && dist < 40) {
				// ovdje aktiviramo UI
                    if(isEasterEgg){
                        npc->getGameWorld()->getNotification()->play(npc->getGameWorld()->getRandomJoke(),sf::milliseconds(5000));
                        //std::cout<<npc->getGameWorld()->getRandomJoke()<<"\n";
                    }else{
                        npc->getGameWorld()->setCurrentDialog(npc->getID());
                        npc->getGameWorld()->getUI("dialogUI")->active = true;
                        npc->getGameWorld()->pause();
                    }


			}

		}
	};
}

#endif
