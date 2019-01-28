#ifndef Springboard_hpp
#define Springboard_hpp

#include "SDL2/SDL.h"

#include "InteractiveObject.hpp"
#include "../../gui/Image.hpp"
#include "../../gui/Sprite.hpp"

class Springboard : public InteractiveObject {

public:
	Springboard(float xSpawn, float ySpawn, SDL_Renderer*& renderer);
	~Springboard();

	void update(int delta);
	void render(SDL_Renderer*& renderer, int width, int height);

	int nextStep();

private:
	Image* spriteSheet;
	Sprite* sprites[3];

	int step;
	int lastStep;
};

#endif