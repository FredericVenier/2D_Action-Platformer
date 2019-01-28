#ifndef Sprite_hpp
#define Sprite_hpp

#include <math.h>

#include "SDL2/SDL.h"

#include "Image.hpp"

class Sprite {

public:
	Sprite(Image*& sheet, int x, int y, int w, int h);
	Sprite(Image*& sheet);
	~Sprite();

	void render(SDL_Renderer*& renderer, float x, float y, int width, int height);

private:
	Image* spriteSheet;
	SDL_Rect* srcRectangle;
};

#endif