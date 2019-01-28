#ifndef InteractiveObject_hpp
#define InteractiveObject_hpp

#include "SDL2/SDL.h"

#include "../Entity.hpp"

class InteractiveObject : public Entity {

public:
	enum Type {
		SPRINGBOARD
	};

	InteractiveObject(float xSpawn, float ySpawn, int width, int height, Type t);
	virtual ~InteractiveObject();

	virtual void update(int delta);
	virtual void render(SDL_Renderer*& renderer, int width, int height);

	virtual int nextStep();

	int getType() const;

private:
	Type type;

};

#endif