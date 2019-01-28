#include "Image.hpp"

Image::Image(char* path, SDL_Renderer*& renderer) {
	texture = NULL;

	SDL_Surface* img = IMG_Load(path);
	
	if(img != NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, img);
		
	} else {
		std::cout << "ERROR: IMG_Load issue (Image) : " << IMG_GetError() << std::endl; //debug
	}

	SDL_FreeSurface(img);
}

Image::~Image() {
	SDL_DestroyTexture(texture);
}

SDL_Texture* Image::getTexture() const {
	return texture;
}