#include "Room.hpp"	

Room::Room() : groundsNbr(0), objectsNbr(0) {

}

Room::Room(int groundsColorR, int groundsColorG, int groundsColorB) : groundsNbr(0), objectsNbr(0) {
	groundsColor[0] = groundsColorR; 
	groundsColor[1] = groundsColorG;
 	groundsColor[2] = groundsColorB;
}

Room::~Room() {
	for(int i(0); i<groundsNbr; i++) {
		delete grounds[i];
	}

	for(int j(0); j<objectsNbr; j++) {
		delete interactiveObjects[j];
	}
}

void Room::update(int delta) {
	for(int i(0); i<objectsNbr; i++) {
		interactiveObjects[i]->update(delta);
	}
}

void Room::render(SDL_Renderer*& renderer, int width, int height) {
	for(int i(0); i<objectsNbr; i++) {
		interactiveObjects[i]->render(renderer, width, height);
	}

	for(int i(0); i<groundsNbr; i++) {
		grounds[i]->printHitBox(renderer, width, height, groundsColor[0], groundsColor[1], groundsColor[2]);
	}
}

void Room::addGround(Entity* newGround) {
	grounds.push_back(newGround);
	groundsNbr++;
}

int Room::getGroundsNbr() const {
	return groundsNbr;
}

Entity* Room::getGround(int i) const {
	if(i<groundsNbr) return grounds[i];
	else return NULL;
}

void Room::addInteractiveObject(InteractiveObject* newObject) {
	interactiveObjects.push_back(newObject);
	objectsNbr++;
}

int Room::getObjectsNbr() const {
	return objectsNbr;
}

InteractiveObject* Room::getInteractiveObject(int i) const {
	if(i<objectsNbr) return interactiveObjects[i];
	else return NULL;
}