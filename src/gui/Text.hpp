#ifndef Text_hpp
#define Text_hpp

#include <string>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class Text {

public:
	Text(std::string lbl);
	~Text();

	void updateRectangle(SDL_Renderer*& renderer, SDL_Rect* button);
	void updateFont(TTF_Font* f,SDL_Renderer*& renderer, SDL_Rect* button);

	SDL_Rect* getRectangle() const;
	SDL_Texture* getTexture() const;

private:
	std::string label;
	TTF_Font* font;
	SDL_Rect* rectangle;
	SDL_Texture* texture;
};

#endif