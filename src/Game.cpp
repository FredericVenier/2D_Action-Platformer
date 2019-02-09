#include "Game.hpp"

Game::Game() : state(START_MENU), quitting(false), menuDeleted(false) {
	menu = new TitleMenu(this);
	rend = NULL;
	player = NULL;
	moth = NULL;
	// moth2 = NULL;
	level = NULL;
}

Game::~Game() {
	if(menu != NULL) delete menu;
	if(player != NULL) delete player;
	if(level != NULL) delete level;
	if(moth != NULL) delete moth;
	// if(moth2 != NULL) delete moth2;
}

void Game::setRenderer(SDL_Renderer*& renderer) {
	rend = renderer;
}

void Game::newGame() {
	state = PLAY;

	level = new Level();
	level->addRoom(new RoomPrototype(rend));

	player = new Player(rend, level);
	moth = new Moth(143.0f,203.0f,Moth::LEFT,rend,level);
	// moth2 = new Moth(294.0f,50.0f,Moth::RIGHT,rend,level);
}

void Game::update(int delta, InputHandler*& inputHandler) {
	switch(state) {
		case START_MENU: //si on est dans le menu de demarrage
			if(menu != NULL) menu->update(delta, inputHandler);

			if(menuDeleted) {
				menuDeleted = false;
				delete menu;
				menu = NULL;
			}
		break;

		case PLAY: //si on joue
			if(player != NULL) {
				player->update(delta, inputHandler);
				level->update(delta);
				moth->update(delta);
				// moth2->update(delta);
			}
		break;

		default:
		break;
	}
}
	
void Game::render(SDL_Renderer*& renderer, int width, int height) {
		switch(state) {
		case START_MENU: //si on est dans le menu de demarrage
			if(menu != NULL) menu->render(renderer, width, height);
		break;

		case PLAY: //si on joue
			if(player != NULL) {
				level->render(renderer, width, height);
				player->render(renderer, width, height);
				moth->render(renderer, width, height);
				// moth2->render(renderer, width, height);
			}
		break;

		default:
		break;
	}
}

void Game::deleteMenu() {
	menuDeleted = true;
}

void Game::setQuitting(bool b) {
	quitting = b;
}

bool Game::isQuitting() const {
	return quitting;
}