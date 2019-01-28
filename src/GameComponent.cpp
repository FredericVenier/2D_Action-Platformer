#include "GameComponent.hpp"

GameComponent::GameComponent() : running(false) {
	game = new Game();
	inputHandler = new InputHandler();

	window = NULL;
	renderer = NULL;
}

GameComponent::~GameComponent() {
	delete game;
	delete inputHandler;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}

void GameComponent::init(const char* title, int xWindow, int yWindow, int width, int height, bool fullScreen) {
	int flags(0);
	if(fullScreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	} else {
		flags = SDL_WINDOW_RESIZABLE;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		running = false;
		std::cout << "ERROR: SDL_Init issue (GameComponent) : " << SDL_GetError() << std::endl; //debug

	} else {
		window = SDL_CreateWindow(title, xWindow, yWindow, width, height, flags);
		if(!window) {
			std::cout << "ERROR: Window Creation issue (GameComponent) : " << SDL_GetError() << std::endl; //debug
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(!renderer) {
			std::cout << "ERROR: Renderer Creation issue (GameComponent) : " << SDL_GetError() << std::endl; //debug
		} else {
			game->setRenderer(renderer);
		}

		if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
			std::cout << "ERROR: IMG_Init issue (GameComponent) : " << IMG_GetError() << std::endl; //debug
		}

		running = true;
	}
}

void GameComponent::run() {
	const int FPSMax(60);
	const float msPerFrame(1000/FPSMax);

	Uint32 frameStart(0);
	int frameTime(1);
	int delta(msPerFrame);

	while(running) {
		frameStart = SDL_GetTicks();

		update(delta);
		render();

		frameTime = SDL_GetTicks() - frameStart;
		if(msPerFrame>frameTime) {
			SDL_Delay(msPerFrame-frameTime);
			delta = msPerFrame;

		} else {
			delta = frameTime;
		}
	}
}

void GameComponent::update(int delta) {
	inputHandler->update();
	game->update(delta, inputHandler);

	running = !(inputHandler->isQuitting() || game->isQuitting());
}

void GameComponent::render() {
	int* width = NULL;
	int* height = NULL;
	width = (int*)malloc(sizeof(int));
	height = (int*)malloc(sizeof(int));
	SDL_GetWindowSize(window, width, height);

	game->render(renderer, *width, *height);
	free(width);
	free(height);

	SDL_RenderPresent(renderer);
}


/*----------------------------------------main----------------------------------------*/

int main(int argc, const char* argv[]) {

	GameComponent* game = new GameComponent();

	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1152, 648, false);
	game->run();

	delete game;

	return 0;
}