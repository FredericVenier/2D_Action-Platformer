#ifndef Cloud_hpp
#define Cloud_hpp

#include "SDL2/SDL.h"

#include "../../../gui/Sprite.hpp"
#include "../../../gui/Image.hpp"

class Cloud {

public:
	Cloud(Image*& spriteSheet, int i);
	~Cloud();
	void init();

	void update(int delta);
	void render(SDL_Renderer*& renderer, int width, int height);

	float getX() const;
	float getY() const;
	int getW() const;
	int getH() const;

	void setSpeed(float s);
	void setY(float y);
	void setX(float x);

private:
	Sprite* sprite;

	float x;
	float y;
	float speed;

	int w;
	int h;
};

#endif