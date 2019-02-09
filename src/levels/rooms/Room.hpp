#ifndef Room_hpp
#define Room_hpp

#include <vector>

#include "SDL2/SDL.h"

#include "../../entities/Entity.hpp"
#include "../../entities/objects/InteractiveObject.hpp"

class Room {

public:
	Room();
	Room(int groundsColorR, int groundsColorG, int groundsColorB);
	virtual ~Room();

	virtual void update(int delta);
	virtual void render(SDL_Renderer*& renderer, int width, int height);

	void addGround(Entity* newGround);
	int getGroundsNbr() const;
	Entity* getGround(int i) const;

	void addInteractiveObject(InteractiveObject* newObject);
	int getObjectsNbr() const;
	InteractiveObject* getInteractiveObject(int i) const;

private:
	std::vector<Entity*> grounds;
	int groundsNbr;
	int groundsColor[3];

	std::vector<InteractiveObject*> interactiveObjects;
	int objectsNbr;
};

#endif