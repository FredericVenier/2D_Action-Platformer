#include "MenuButton.hpp"
	

MenuButton::MenuButton(std::string lbl, int n) : id(n) {
	rectangle = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rectangle->x = 0;
    rectangle->y = 0;
    rectangle->w = 0;
    rectangle->h = 0;

    text = new Text(lbl);
}

MenuButton::~MenuButton() {
	free(rectangle);
	delete text;
}

bool MenuButton::contains(int x, int y) {
	if (rectangle->x + rectangle->w <= x) return false;
	else if (rectangle->x >= x) return false;
	else if (rectangle->y + rectangle->h <= y) return false;
	else if (rectangle->y >= y) return false;

	return true;
}

void MenuButton::render(SDL_Renderer*& renderer, int width, int height, int selected, int buttonsNbr) {
	//on donne les bonnes dimensions/position au rectangle
	rectangle->x = width/3; //le bouton fait un tiers de la largeur de l'ecran et est centre
	rectangle->w = width/3;
	rectangle->h = height/7; //le bouton fait un septieme de l'ecran et l'ensemble des boutons est centre, 
							 //et les boutons sont separes d'un quart de la taille d'un bouton
							 //c'est bien s'il a au plus 4 boutons
	rectangle->y = height/2 - rectangle->h*buttonsNbr/2 - (buttonsNbr/2 - 1/2)*rectangle->h/4 + id*(rectangle->h + rectangle->h/4);

	//on affiche le bouton
	SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
	SDL_RenderFillRect(renderer, rectangle);
	if(selected == id) {
		//on affiche la selection autour du bouton
		SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
		SDL_RenderDrawRect(renderer, rectangle);
	}

	//on affiche le label
	if(text->getRectangle()->w != 0) {
		SDL_RenderCopy(renderer, text->getTexture(), NULL, text->getRectangle());
	}
}

void MenuButton::updateTextFont(TTF_Font* f, SDL_Renderer*& renderer) {
	text->updateFont(f, renderer, rectangle);
}