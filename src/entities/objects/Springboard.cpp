#include "Springboard.hpp"

Springboard::Springboard(float xSpawn, float ySpawn, SDL_Renderer*& renderer) : InteractiveObject(xSpawn, ySpawn, 14, 8, SPRINGBOARD),
step(0), lastStep(0) {
	spriteSheet = new Image((char*)"res/images/objects/springboard.png", renderer);

	for(int i(0); i<3; i++) {
		sprites[i] = new Sprite(spriteSheet, i*16, 0, 16, 9);
	}
}

Springboard::~Springboard() {
	for(int i(0); i<3; i++) {
		delete sprites[i];
	}
}

void Springboard::update(int delta) {
	if(step>=2) nextStep(); //si on est en position haute on fait defiler automatiquement les positions
	if(step>4) step = 0; //si on a fini l'anim on revient en pos initiale

	if (lastStep == 1 && step == 1) { //pour ne pas rester bloquer en position basse
		nextStep();
	}

	lastStep = step;
}

void Springboard::render(SDL_Renderer*& renderer, int width, int height) {
	switch(step) {
		case 1:
			sprites[1]->render(renderer, x-1, y-3, width, height); //step = 1 -> bot
			break;
		case 3:
			sprites[2]->render(renderer, x-1, y-1, width, height); //step = 3 || 4 -> top
			break;
		case 4:
			sprites[2]->render(renderer, x - 1, y - 1, width, height);
			break;
		default:
			sprites[0]->render(renderer, x-1, y-1, width, height); //step = 0 || 5 -> idle
			break;
	}
}

int Springboard::nextStep() {
	switch(++step) {
		case 1:
			setHitBox(x, y+2, 14, 6);
			break;
		case 2:
			setHitBox(x, y-2, 14, 8);
			break;
		default:
			break;
	}

	return step;
}