#include "Game.hpp"

Game::Game() : quitting(false), menuDeleted(false) {
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
	level = new Level();
	level->addRoom(new RoomPrototype(rend));

	player = new Player(rend, level);
}

void Game::update(int delta, InputHandler*& inputHandler) {
	//si on est dans un menu
	if(menu != NULL) {
		menu->update(delta, inputHandler);
	}

	if(menuDeleted) {
		menuDeleted = false;
		delete menu;
		menu = NULL;
	}


	//si on joue
	if(player != NULL) {
		player->update(delta, inputHandler);
		level->update(delta);
	}
}
	
void Game::render(SDL_Renderer*& renderer, int width, int height) {
	//si on est dans un menu
	if(menu != NULL) {
		menu->render(renderer, width, height);
	}

	//si on joue
	if(player != NULL) {
		level->render(renderer, width, height, player->getX());
		player->render(renderer, width, height);
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