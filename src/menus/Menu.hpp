#ifndef Menu_hpp
#define Menu_hpp

#include "SDL2/SDL.h"

#include "../InputHandler.hpp"

class Game;

class Menu {

public:
	Menu(Game* g);
	virtual ~Menu();

	virtual void update(int delta, InputHandler*& inputHandler);
	virtual void render(SDL_Renderer*& renderer, int width, int height);

protected:
	Game* game;

private:

};

#endif