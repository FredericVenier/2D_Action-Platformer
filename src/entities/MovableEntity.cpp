#include "MovableEntity.hpp"

MovableEntity::MovableEntity(float xSpawn, float ySpawn, int width, int height, float entitySpeed, Level*& lvl) : Entity(xSpawn, ySpawn, width, height), 
speed(entitySpeed), speedX(0.0f), speedY(0.0f), fallingTime(0), xVelocity(0.0f), yVelocity(0.0f), collidingGround(false), level(lvl) {

}

MovableEntity::~MovableEntity() {

}

void MovableEntity::update(int delta, bool falling) {
	if (falling) fallingTime += delta;
	else fallingTime = 0;

	yVelocity = GRAVITY*fallingTime/1000 - speedY; //gravity

	float oldX(x);
	float oldY(y);

	x += speedX*delta;
	y += yVelocity*delta/1000;

	//collisions
	collidingGround = false;
	for(int i(0); i<level->getActualRoom()->getGroundsNbr(); i++) {
		if(isInside(level->getActualRoom()->getGround(i))) { //s'il y a collision avec une hitbox du decor
			//on gere d'abord les collisions sur x
			for(int j=0; j<h; j=j+3) {
				if(level->getActualRoom()->getGround(i)->contains(x+w, y+j) || level->getActualRoom()->getGround(i)->contains(x, y+j)) {
					x = oldX;
				}
			}

			//on gere les collisions sur y
			for(int j=0; j<w; j=j+3) {
				if(level->getActualRoom()->getGround(i)->contains(x+j, y)) { //collision depuis le haut
					//if(x==oldX) x += speedX * 0.66f * delta;

					y = oldY;
					setSpeedY(0.0f);

				} else if (level->getActualRoom()->getGround(i)->contains(x+j, y+h)) { //collision depuis le bas
					//if (x == oldX) x += speedX * delta;

					y = level->getActualRoom()->getGround(i)->getY()-h;
					collidingGround = true;
					setSpeedY(0.0f);
				}
			}
		}
	}

	xVelocity = (x-oldX)/delta;
	yVelocity = (y-oldY)/delta;
}

void MovableEntity::render(SDL_Renderer*& renderer, int width, int height) {

}

void MovableEntity::initSpeedX() {
	speedX = 0.0f;
}

void MovableEntity::initFallingTime() {
	setFallingTime(0.0f);
}

void MovableEntity::setFallingTime(float t) {
	fallingTime = t;
}

void MovableEntity::horizontalDeceleration(float coefficient) {
	speedX = xVelocity*coefficient;
}

void MovableEntity::horizontalMove(float coefficient) {
	speedX = coefficient*speed;
}

void MovableEntity::setSpeedY(float newSpeed) {
	speedY = newSpeed;
}

bool MovableEntity::isFalling() {
	return (yVelocity>0);
}