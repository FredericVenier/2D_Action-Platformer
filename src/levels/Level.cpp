#include "Level.hpp"

Level::Level() : roomsNbr(0), actualRoom(0) {

}

Level::~Level() {
	for(int i(0); i<roomsNbr; i++) {
		delete rooms[i];
	}
}

void Level::update(int delta) {
	if(actualRoom < roomsNbr) {
		rooms[actualRoom]->update(delta);
	}
}

void Level::render(SDL_Renderer*& renderer, int width, int height, float playerX) {
	if(actualRoom < roomsNbr) rooms[actualRoom]->render(renderer, width, height, playerX);
}

void Level::addRoom(Room* room) {
	rooms.push_back(room);
	roomsNbr++;
}

Room* Level::getActualRoom() {
	if(actualRoom < roomsNbr) return rooms[actualRoom];
	else return NULL;
}