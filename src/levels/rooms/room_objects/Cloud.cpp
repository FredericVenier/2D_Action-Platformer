#include "Cloud.hpp"

Cloud::Cloud(Image*& spriteSheet, int i) : w(160), h(31) {
	sprite = new Sprite(spriteSheet, i*w, 0, w, h);

	init();
}

Cloud::~Cloud() {
	delete sprite;
}

void Cloud::init() {
	x = -w-30;
	y = 0.0f;
	speed = 0.0f;
}

void Cloud::update(int delta) {
	x += (float)(delta*speed);

	if(x>426) {
		init();
	}
}

void Cloud::render(SDL_Renderer*& renderer, int width, int height) {
	sprite->render(renderer, x, y, width, height);
}

float Cloud::getX() const {
	return x;
}

float Cloud::getY() const {
	return y;
}

int Cloud::getW() const {
	return w;
}

int Cloud::getH() const {
	return h;
}

void Cloud::setSpeed(float s) {
	speed = s;
}

void Cloud::setY(float newY) {
	y = newY;
}

void Cloud::setX(float newX) {
	x = newX;
}