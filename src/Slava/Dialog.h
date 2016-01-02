#ifndef __DIALOG_H
#define __DIALOG_H

#include <string>
#include <memory>
#include <vector>

namespace slava
{
	class GameWorld;
	typedef struct _dialog
	{
		std::string question;
		std::vector<std::string> answers;
		std::shared_ptr<struct _dialog> next[4];
		void(*action[4]) (GameWorld*);
	} DialogNode;

	class Dialog
	{
	public:
		static std::shared_ptr<DialogNode> createDialog() {
			auto dialog = std::make_shared<DialogNode>();
			for (int i = 0; i < 4; ++i) {
				dialog->next[i] = NULL;
				dialog->action[i] = NULL;
			}
			dialog->answers.resize(4);
			return dialog;
		}

		static void connect(std::shared_ptr<DialogNode>& node, int i, std::shared_ptr<DialogNode>& second) {
			if (i < 0 || i >= 4) return;
			node->next[i] = second;
		}

		static void setAction(std::shared_ptr<DialogNode>& node, int i, void(*func) (GameWorld*)) {
			if (i < 0 || i >= 4) return;
			node->action[i] = func;
		}

		/*static std::string* createAnswers(const char* first, const char* second, const char* third, const char* fourth) {
			std::string niz[] = {first, second, third, fourth};
			return niz;
		}*/

	};
}

#endif
