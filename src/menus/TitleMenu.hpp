#ifndef TitleMenu_hpp
#define TitleMenu_hpp

#include <vector>
#include <string>

#include "ButtonsMenu.hpp"
#include "Menu.hpp"

class TitleMenu : public ButtonsMenu {

public:
	TitleMenu(Game* g);
	~TitleMenu();

	void update(int delta, InputHandler*& inputHandler);

private:
	void quit(Game*& game);
	void newGame(Game*& game);

};

#endif