#ifndef MirrorAnimation_hpp
#define MirrorAnimation_hpp

#include "SDL2/SDL.h"

#include "Animation.hpp"

class MirrorAnimation : public Animation {

public:
	MirrorAnimation(char* path, int line, int nSprites, int frameDelay,int w, int h, int shiftValue, SDL_Renderer*& renderer);
	~MirrorAnimation();

	void render(SDL_Renderer*& renderer, float x, float y, int width, int height);
	
private:
	int shiftX;
};

#endif