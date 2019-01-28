#include "ButtonsMenu.hpp"

ButtonsMenu::ButtonsMenu(Game* g) : Menu(g), buttonsNbr(0), selected(0), oldW(0), activated(-1) {
	if(TTF_Init() == -1) {
		std::cout << "ERROR: TTF_Init issue (ButtonsMenu) : " << TTF_GetError() << std::endl; //debug
	}

	font = NULL;
}

ButtonsMenu::~ButtonsMenu() {
	for(int i(0); i<buttonsNbr; i++) {
		delete buttons[i];
	}

	TTF_CloseFont(font);
	TTF_Quit();
}

void ButtonsMenu::setButtons(std::vector<std::string> labels) {
	buttonsNbr = labels.size();

	for(int i(0); i<buttonsNbr; i++) {
		buttons.push_back(new MenuButton(labels[i],buttons.size()));
	}
}

void ButtonsMenu::update(int delta, InputHandler*& inputHandler) {
	inputHandler->update();
	
	if(inputHandler->keys[SDL_SCANCODE_RETURN] || inputHandler->keys[SDL_SCANCODE_KP_ENTER]) activated = selected;


	if(inputHandler->keys[SDL_SCANCODE_W] || inputHandler->keys[SDL_SCANCODE_UP]) {
		selected--;
		inputHandler->keys[SDL_SCANCODE_W] = inputHandler->keys[SDL_SCANCODE_UP] = false;
	}

	if(inputHandler->keys[SDL_SCANCODE_S] || inputHandler->keys[SDL_SCANCODE_DOWN]) {
		selected++;
		inputHandler->keys[SDL_SCANCODE_S] = inputHandler->keys[SDL_SCANCODE_DOWN] = false;
	} 

	if(selected < 0) selected = 0;
	else if(selected >= buttonsNbr) selected = buttonsNbr-1;
}

void ButtonsMenu::render(SDL_Renderer*& renderer, int width, int height) {
	//on met un fond de couleur
	SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
	SDL_RenderClear(renderer);

	//on affiche les boutons
	for(int i(0); i<buttonsNbr; i++) {
		buttons[i]->render(renderer, width, height, selected, buttonsNbr);
	}

	//si on n'a pas encore charge la police ou si on a change de taille d'ecran, on change la taille de la police
	if(oldW != width) {
		TTF_CloseFont(font);

		font = TTF_OpenFont("res/fonts/font.ttf", width/800*40);
		if(font == NULL) {
			std::cout << "ERROR: TTF_OpenFont issue (ButtonsMenu) : " << TTF_GetError() << std::endl; //debug
		}

		for(int i(0); i<buttonsNbr; i++) {
			buttons[i]->updateTextFont(font, renderer);
		}

		oldW = width;
	}
}