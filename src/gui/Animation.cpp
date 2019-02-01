#include "Animation.hpp"

Animation::Animation(char* path, int line, int nSprites, int frameDelay, int w, int h, SDL_Renderer*& renderer) : spritesNbr(nSprites), delay(0), fmDelay(frameDelay), iterator(0) {
	spriteSheet = new Image(path, renderer);

	for(int i(0); i<nSprites; i++) {
		sprites.push_back(new Sprite(spriteSheet, i*w, (line-1)*h, w, h));
	}
}

Animation::~Animation() {
	for(int i(0); i<spritesNbr; i++) {
		delete sprites[i];
	}

	delete spriteSheet;
}


void Animation::init() {
	iterator = 0;
	delay = 0;
}

void Animation::update(int delta) {
	delay += delta;

	if(fmDelay - delay <= 0) {
		if(++iterator >= spritesNbr) {
			iterator = 0;
		}

		delay = 0;
	}
	
}

void Animation::render(SDL_Renderer*& renderer, float x, float y, int width, int height) {
	sprites[iterator]->render(renderer, x, y, width, height);
}