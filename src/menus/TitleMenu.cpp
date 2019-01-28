#include "TitleMenu.hpp"
#include "../Game.hpp"
	
using namespace std;

TitleMenu::TitleMenu(Game* g) : ButtonsMenu(g) {
	vector<string> labels;
	labels.push_back("New Game");
	labels.push_back("Quit");

	setButtons(labels);
}

TitleMenu::~TitleMenu() {
	
}

void TitleMenu::update(int delta, InputHandler*& inputHandler) {
	ButtonsMenu::update(delta, inputHandler);

	switch(ButtonsMenu::activated) {
		case -1:
			break;

		case 0:
			newGame(Menu::game);
			break;

		case 1:
			quit(Menu::game);
			break;

		default:
			break;
	}

	if(inputHandler->keys[SDL_SCANCODE_ESCAPE]) {
		quit(Menu::game);
	}
}

void TitleMenu::newGame(Game*& game) {
	game->deleteMenu();
	game->newGame();
}

void TitleMenu::quit(Game*& game) {
	game->deleteMenu();
	game->setQuitting(true);
}