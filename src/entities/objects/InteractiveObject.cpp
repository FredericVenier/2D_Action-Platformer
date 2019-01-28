#include "InteractiveObject.hpp"

InteractiveObject::InteractiveObject(float xSpawn, float ySpawn, int width, int height, Type t) : Entity(xSpawn, ySpawn, width, height), type(t) {

}

InteractiveObject::~InteractiveObject() {

}

void InteractiveObject::update(int delta) {

}
	
void InteractiveObject::render(SDL_Renderer*& renderer, int width, int height) {

}

int InteractiveObject::nextStep() {
	return -1;
}

int InteractiveObject::getType() const {
	return type;
}