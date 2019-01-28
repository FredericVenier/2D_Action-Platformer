#ifndef Entity_hpp
#define Entity_hpp

#include "SDL2/SDL.h"

class Entity {

public:
	Entity(float xSpawn, float ySpawn, int width, int height);
	virtual ~Entity();

	virtual void update(int delta);
	virtual void render(SDL_Renderer*& renderer, int width, int height);

	void setHitBox(float newX, float newY, int width, int height);
	void setW(int width);
	void setH(int height);

	float getX() const;
	float getY() const;
	int getW() const;
	int getH() const;

	bool isInside(float x1, float y1, int w1, int h1);
	bool isInside(Entity* e);
	bool contains(float x1, float y1);

	void printHitBox(SDL_Renderer*& renderer, int width, int height, int colorR=255, int colorG=0, int colorB=0);

protected:
	float x;
	float y;
	int w;
	int h;
};

#endif