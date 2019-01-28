#ifndef MovableEntity_hpp
#define MovableEntity_hpp

#include "SDL2/SDL.h"

#include "Entity.hpp"
#include "../levels/Level.hpp"
#include "../InputHandler.hpp"

class MovableEntity : public Entity {

public:
	MovableEntity(float xSpawn, float ySpawn, int width, int height, float entitySpeed, Level*& lvl);
	virtual ~MovableEntity();

	virtual void update(int delta, InputHandler*& inputHandler, bool falling);
	virtual void render(SDL_Renderer*& renderer, int width, int height);

private:
	float speed;

	float speedX;
	float speedY;

	int fallingTime;

protected:
	
	float xVelocity;
	float yVelocity;

	bool collidingGround;

	Level* level;

	void initSpeedX();
	void initFallingTime();
	void setFallingTime(float t);
	void setSpeedY(float newSpeed);
	void horizontalDeceleration(float coefficient);
	void horizontalMove(float sign);

	bool isFalling(); //return true si l'entite se dirige vers le bas
};

#endif