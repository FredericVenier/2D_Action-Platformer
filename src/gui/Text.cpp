#include "Text.hpp"

Text::Text(std::string lbl) : label(lbl) {
	rectangle = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rectangle->x = 0;
	rectangle->y = 0;
	rectangle->w = 0;
	rectangle->h = 0;

	texture = NULL;
	font = NULL;
}

Text::~Text() {
	SDL_DestroyTexture(texture);
	free(rectangle);
}

void Text::updateRectangle(SDL_Renderer*& renderer, SDL_Rect* button) {
	SDL_Color color = {20, 20, 20, 255};
	SDL_Surface* surface = TTF_RenderText_Solid(font, label.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &rectangle->w, &rectangle->h);
	rectangle->x = button->x + (button->w-rectangle->w)/2;
	rectangle->y = button->y + (button->h-rectangle->h)/2;
	SDL_FreeSurface(surface);
}

SDL_Rect* Text::getRectangle() const {
	return rectangle;
}

SDL_Texture* Text::getTexture() const {
	return texture;
}

void Text::updateFont(TTF_Font* f, SDL_Renderer*& renderer, SDL_Rect* button) {
	font = f;
	if(font == NULL) {
		std::cout << "ERROR: font NULL issue (Text) : " << std::endl; //debug
	}

	updateRectangle(renderer, button);
}