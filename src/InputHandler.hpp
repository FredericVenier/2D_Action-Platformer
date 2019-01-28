#ifndef InputHandler_hpp
#define InputHandler_hpp

#include "SDL2/SDL.h"

class InputHandler {

public:
	InputHandler();
	~InputHandler();

	void update();

	bool isQuitting() const;

	bool keys[SDL_NUM_SCANCODES];
	bool mouseButtons[5];

	int mouseX;
	int mouseY;

private:
	int keysLength;

	bool quitting;

	int mouseButtonsLength;
};

#endif