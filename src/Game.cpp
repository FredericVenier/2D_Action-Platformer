#include "Game.hpp"

Game::Game() : state(START_MENU), quitting(false), menuDeleted(false) {
	menu = new TitleMenu(this);
	rend = NULL;
	player = NULL;
	level = NULL;
}

Game::~Game() {
	delete player;
	delete level;
}

void Game::setRenderer(SDL_Renderer*& renderer) {
	rend = renderer;
}

void Game::newGame() {
	state = PLAY;

	level = new Level();
	level->addRoom(new RoomPrototype(rend));

	player = new Player(rend, level);
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
				level->render(renderer, width, height, player->getX());
				player->render(renderer, width, height);
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