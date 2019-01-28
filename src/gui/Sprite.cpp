#include "Sprite.hpp"

Sprite::Sprite(Image*& sheet, int x, int y, int w, int h) : spriteSheet(sheet){
	srcRectangle = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	srcRectangle->x = x;
	srcRectangle->y = y;
	srcRectangle->w = w;
	srcRectangle->h = h;
}

Sprite::Sprite(Image*& sheet) : spriteSheet(sheet) {
	srcRectangle = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	srcRectangle->x = 0;
	srcRectangle->y = 0;
	SDL_QueryTexture(spriteSheet->getTexture(), NULL, NULL, &srcRectangle->w, &srcRectangle->h);
}

Sprite::~Sprite() {
	free(srcRectangle);
}

void Sprite::render(SDL_Renderer*& renderer, float x, float y, int width, int height) {
	SDL_Rect dstRectangle = {(int)roundf(x*width/426), (int)roundf(y*height/240), (int)roundf(width*srcRectangle->w/426), (int)roundf(height*srcRectangle->h/240)}; //pour une resolution de base en 426x240

	SDL_RenderCopy(renderer, spriteSheet->getTexture(), srcRectangle, &dstRectangle);
}