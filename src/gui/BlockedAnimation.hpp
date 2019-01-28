#ifndef BlockedAnimation_hpp
#define BlockedAnimation_hpp

#include "SDL2/SDL.h"

#include "Animation.hpp"

class BlockedAnimation : public Animation {

public:
	BlockedAnimation(char* path, int line, int nSprites, int frameDelay,int w, int h, SDL_Renderer*& renderer);
	BlockedAnimation(char* path, int line, int nSprites, int frameDelay,int w, int h, SDL_Renderer*& renderer, int loopFrame);
	~BlockedAnimation();

	void update(int delta);

	void init();
	
private:
	int frame;
	bool firstLoop;
};

#endif