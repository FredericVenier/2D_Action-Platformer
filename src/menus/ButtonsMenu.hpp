#ifndef ButtonsMenu_hpp
#define ButtonsMenu_hpp

#include <vector>
#include <string>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "Menu.hpp"
#include "menu_objects/MenuButton.hpp"

class ButtonsMenu : public Menu {

public:
	ButtonsMenu(Game* g);
	virtual ~ButtonsMenu();
	void setButtons(std::vector<std::string> labels);

	virtual void update(int delta, InputHandler*& inputHandler);
	virtual void render(SDL_Renderer*& renderer, int width, int height);

private:
	std::vector<MenuButton*> buttons;
	int buttonsNbr; //number of buttons
	int selected;

	TTF_Font* font;

	int oldW;

protected:
	int activated;
};

#endif