#include "InputHandler.hpp"

InputHandler::InputHandler() : keysLength(SDL_NUM_SCANCODES), quitting(false), mouseButtonsLength(5) {
	for(int i(0); i<keysLength; i++) {
		keys[i] = false;
	}

	for(int i(0); i<mouseButtonsLength; i++) {
		mouseButtons[i] = false;
	}

	int *tempX = NULL, *tempY = NULL;
	tempX = (int*)malloc(sizeof(int));
	tempY = (int*)malloc(sizeof(int));
	SDL_GetMouseState(tempX,tempY);
	mouseX = *tempX;
	mouseY = *tempY;
	free(tempX);
	free(tempY);
}

InputHandler::~InputHandler() {

}

void InputHandler::update() {
	SDL_Event event;
	if(SDL_PollEvent(&event)) {

		switch(event.type) {
			case SDL_QUIT:
				quitting = true;
				break;
	
			case SDL_KEYDOWN:
				keys[event.key.keysym.scancode] = true;
				break;
	
			case SDL_KEYUP:
				keys[event.key.keysym.scancode] = false;
				break;

			case SDL_MOUSEMOTION:
				mouseX = event.motion.x;
				mouseY = event.motion.y;
			break;

			case SDL_MOUSEBUTTONDOWN:
	            // mouseButtons[event.button.button] = true;
	            break;

	        case SDL_MOUSEBUTTONUP:
				// mouseButtons[event.button.button] = false;
				break;
	
			default:
				break;
		}
	}
}

bool InputHandler::isQuitting() const {
	return quitting;
}