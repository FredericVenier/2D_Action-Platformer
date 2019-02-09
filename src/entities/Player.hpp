#ifndef Player_hpp
#define Player_hpp

#include "SDL2/SDL.h"

#include "../gui/Animation.hpp"
#include "../gui/BlockedAnimation.hpp"
#include "../gui/MirrorAnimation.hpp"
#include "../InputHandler.hpp"
#include "MovableEntity.hpp"
#include "../levels/Level.hpp"
#include "objects/InteractiveObject.hpp"

class Player : public MovableEntity {

public:
	Player(SDL_Renderer*& renderer, Level*& level);
	~Player();

	void update(int delta, InputHandler*& inputHandler);
	void render(SDL_Renderer*& renderer, int width, int height);

private:
	enum State
	{
		IDLE,
		RUN,
		SQUAT,
		JUMP,
		ATTACK_ONE,
		ATTACK_TWO,
		ATTACK_THREE,
		STATE_EOE //End Of Enumeration
	};

	enum Facing
	{
		LEFT,
		RIGHT,
		FACING_EOE //End Of Enumeration
	};

	State state;
	Facing facing;

	bool right;
	bool left;
	bool rightLeft;

	bool up;
	bool down;

	bool attack;

	int cooldown;
	int combo;

	Animation* animations[STATE_EOE][FACING_EOE];

	void updateInput(InputHandler*& inputHandler);
	void updateState(bool updateLeft, bool updateRight);

	void moveX(bool updateLeft, bool updateRight);

	void setState(State newState);
	void setFacing(Facing newFacing);

	void doObjectsCollision();
};

#endif