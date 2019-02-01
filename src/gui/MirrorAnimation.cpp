#include "MirrorAnimation.hpp" 

MirrorAnimation::MirrorAnimation(char* path, int line, int nSprites, int frameDelay, int w, int h, int shiftValue, SDL_Renderer*& renderer) : Animation(path, line, nSprites, frameDelay, w, h, renderer), shiftX(shiftValue) {

}

MirrorAnimation::~MirrorAnimation() {

}

void MirrorAnimation::render(SDL_Renderer*& renderer, float x, float y, int width, int height) {
	sprites[iterator]->render(renderer, x+shiftX, y, width, height, true);
}