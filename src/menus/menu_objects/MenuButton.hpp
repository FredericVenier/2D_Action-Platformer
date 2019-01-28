#ifndef MenuButton_hpp
#define MenuButton_hpp

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "../../gui/Text.hpp"

class MenuButton {

public:
	MenuButton(std::string lbl, int n);
	~MenuButton();

	void render(SDL_Renderer*& renderer, int width, int height, int selected, int buttonsNbr);

	bool contains(int x, int y);

	void updateTextFont(TTF_Font* f, SDL_Renderer*& renderer);

private:
	Text* text;

	int id;
	SDL_Rect* rectangle;

};

#endif