#ifndef GameComponent_hpp
#define GameComponent_hpp

#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Game.hpp"
#include "InputHandler.hpp"

class GameComponent {

public:
	GameComponent();
	~GameComponent();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	
	void run();
	void update(int delta);
	void render();

private:
	bool running;

	Game* game;
	SDL_Window* window;
	SDL_Renderer* renderer;
	InputHandler* inputHandler;
};

#endif