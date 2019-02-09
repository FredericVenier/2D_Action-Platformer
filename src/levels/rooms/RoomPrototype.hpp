#ifndef RoomPrototype_hpp
#define RoomPrototype_hpp

#include <vector>
#include <cstdlib>
#include <ctime>

#include "SDL2/SDL.h"

#include "Room.hpp"
#include "../../gui/Sprite.hpp"
#include "../../gui/Image.hpp"
#include "room_objects/Cloud.hpp"
#include "../../entities/Entity.hpp"
#include "../../entities/objects/Springboard.hpp"

class RoomPrototype : public Room {

public:
	RoomPrototype(SDL_Renderer*& renderer);
	~RoomPrototype();

	void update(int delta);
	void render(SDL_Renderer*& renderer, int width, int height);

	void initClouds();

private:
	Image* backdropImg;
	Sprite* backdrop;

	Image* cloudsSpriteSheet;
	std::vector<Cloud*> clouds;
	int cloudsNbr;
	int cloudTimer;
	float lastCloudY;

	Image* backgroundImg;
	Sprite* background;

	Image* frontgroundImg;
	Sprite* frontground;
};

#endif