#ifndef __DIALOG_UI_H
#define __DIALOG_UI_H

#include "UI.h"
#include "Dialog.h"
#include <memory>

namespace slava
{
	typedef std::shared_ptr<sf::Font> FontPtr;
	class DialogUI : virtual public UI
	{
	private:
		std::shared_ptr<DialogNode> cpy;
		bool cpySet = false;
		sf::Text question;
		sf::Text answers[4];
		sf::RectangleShape sQuestion;
		sf::RectangleShape sAnswers[4];
	public:
		DialogUI(sf::Font&);
		void control(GameWorld*);
		void draw(sf::RenderWindow&);
	};
}

#endif
