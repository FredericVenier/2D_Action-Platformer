#ifndef Moth_hpp
#define Moth_hpp

#include "SDL2/SDL.h"

#include "../../gui/Animation.hpp"
#include "../../gui/MirrorAnimation.hpp"
#include "../MovableEntity.hpp"

class Moth : public MovableEntity {

public:
	enum Facing
	{
		LEFT,
		RIGHT,
		FACING_EOE //End Of Enumeration
	};

	Moth(int xSpawn, int ySpawn, Facing face, SDL_Renderer*& renderer, Level*& level);
	~Moth();

	void update(int delta);
	void render(SDL_Renderer*& renderer, int width, int height);

private:
	enum State
	{
		IDLE,
		JUMP,
		STATE_EOE //End Of Enumeration
	};

	State state;
	Facing facing;

	Animation* animations[STATE_EOE][FACING_EOE];

	void setState(State newState);
	void setFacing(Facing newFacing);
};

#endif