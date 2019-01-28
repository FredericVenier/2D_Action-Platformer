#include "Entity.hpp"

Entity::Entity(float xSpawn, float ySpawn, int width, int height) : x(xSpawn), y(ySpawn), w(width), h(height) {

}

Entity::~Entity() {

}

void  Entity::update(int delta) {

}

void  Entity::render(SDL_Renderer*& renderer, int width, int height) {

}

void Entity::setHitBox(float newX, float newY, int width, int height) {
	x = newX;
	y = newY;
	w = width;
	h = height;
}

void Entity::setW(int width) {
	w = width;
}

void Entity::setH(int height) {
	h = height;
}

float Entity::getX() const {
	return x;
}

float Entity::getY() const {
	return y;
}

int Entity::getW() const {
	return w;
}

int Entity::getH() const {
	return h;
}

bool Entity::isInside(float x1, float y1, int w1, int h1) {
	if (x + w < x1) return false;
	if (x > x1+w1) return false;

	if (y + h < y1) return false;
	if (y > y1+h1) return false;

	return true;
}

bool Entity::isInside(Entity* e) {
	return isInside(e->getX(), e->getY(), e->getW(), e->getH());
}

bool Entity::contains(float x1, float y1) {
	if (x + w < x1) return false;
	if (x > x1) return false;

	if (y + h < y1) return false;
	if (y > y1) return false;

	return true;
}

void Entity::printHitBox(SDL_Renderer*& renderer, int width, int height, int colorR, int colorG, int colorB) {
	SDL_Rect rectangle = {(int)roundf(x*width/426), (int)roundf(y*height/240), width*w/426, height*h/240};

	//on affiche le bouton
	SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}