#ifndef Image_hpp
#define Image_hpp

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Image {

public:
	Image(char* path, SDL_Renderer*& renderer);
	~Image();

	SDL_Texture* getTexture() const;

private:
	SDL_Texture* texture;
};

#endif