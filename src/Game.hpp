#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"

#include "InputHandler.hpp"
#include "menus/Menu.hpp"
#include "menus/TitleMenu.hpp"
#include "entities/Player.hpp"
#include "entities/enemies/Moth.hpp"
#include "levels/Level.hpp"
#include "levels/rooms/RoomPrototype.hpp"

class Game {

public:
	Game();
	~Game();
	void setRenderer(SDL_Renderer*& renderer);

	void newGame();
	void update(int delta, InputHandler*& inputHandler);
	void render(SDL_Renderer*& renderer, int width, int height);

	void setQuitting(bool b);
	bool isQuitting() const;

	void deleteMenu();

private:
	enum State
	{
		START_MENU,
		PLAY,
		EOE //End Of Enumeration
	};

	State state;
	
	bool quitting;

	Menu* menu;
	bool menuDeleted;

	Player* player;
	Moth* moth;
	// Moth* moth2;

	Level* level;

	SDL_Renderer* rend;
};

#endif