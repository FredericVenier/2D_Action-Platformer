#ifndef Animation_hpp
#define Animation_hpp

#include <vector>

#include "SDL2/SDL.h"

#include "Image.hpp"
#include "Sprite.hpp"

class Animation {

public:
	Animation(char* path, int line, int nSprites, int frameDelay,int w, int h, SDL_Renderer*& renderer);
	virtual ~Animation();

	virtual void init();

	virtual void update(int delta);
	virtual void render(SDL_Renderer*& renderer, float x, float y, int width, int height);

private:
	int spritesNbr;

	int delay;
	int fmDelay;

	Image* spriteSheet;

protected:
	std::vector<Sprite*> sprites;
	int iterator;
};

#endif