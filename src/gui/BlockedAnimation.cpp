#include "BlockedAnimation.hpp" 

BlockedAnimation::BlockedAnimation(char* path, int line, int nSprites, int frameDelay, int w, int h, SDL_Renderer*& renderer) : Animation(path, line, nSprites, frameDelay, w, h, renderer), frame(nSprites-1), firstLoop(true) {

}

BlockedAnimation::BlockedAnimation(char* path, int line, int nSprites, int frameDelay, int w, int h, SDL_Renderer*& renderer, int loopFrame) : Animation(path, line, nSprites, frameDelay, w, h, renderer), frame(loopFrame), firstLoop(true) {

}

BlockedAnimation::~BlockedAnimation() {

}


void BlockedAnimation::update(int delta) {
	Animation::update(delta);

	if (firstLoop && Animation::getIterator() != 0) firstLoop = false;

	if (!firstLoop && Animation::getIterator() == 0) Animation::setIterator(frame);
}

void BlockedAnimation::init() {
	firstLoop = true;
	Animation::init();
}