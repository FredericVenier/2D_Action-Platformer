#ifndef Level_hpp
#define Level_hpp

#include <vector>

#include "SDL2/SDL.h"

#include "rooms/Room.hpp"

class Level {

public:
	Level();
	~Level();

	void update(int delta);
	void render(SDL_Renderer*& renderer, int width, int height);

	void addRoom(Room* room);

	Room* getActualRoom();

private:
	std::vector<Room*> rooms;
	int roomsNbr;

	int actualRoom;
};

#endif