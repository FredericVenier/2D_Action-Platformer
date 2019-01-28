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
	void render(SDL_Renderer*& renderer, float x, float y, int width, int height);

	int getIterator() const;
	void setIterator(int i);

private:
	std::vector<Sprite*> sprites;
	int spritesNbr;
	int iterator;

	int delay;
	int fmDelay;

	Image* spriteSheet;
};

#endif