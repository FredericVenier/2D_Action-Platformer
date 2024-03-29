#ifndef MovableEntity_hpp
#define MovableEntity_hpp

#ifndef GRAVITY
#define H_MAX 16								//hauteur max du saut (en px)
#define T_H_MAX 0.24f							//temps pour atteindre hmax (en s)
#define GRAVITY  (2*H_MAX)/(T_H_MAX*T_H_MAX)
#endif

#include "SDL2/SDL.h"

#include "Entity.hpp"
#include "../levels/Level.hpp"
#include "../InputHandler.hpp"

class MovableEntity : public Entity {

public:
	MovableEntity(float xSpawn, float ySpawn, int width, int height, float entitySpeed, Level*& lvl);
	virtual ~MovableEntity();

	virtual void update(int delta, bool falling);
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