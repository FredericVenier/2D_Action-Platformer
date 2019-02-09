#include "Moth.hpp"

Moth::Moth(int xSpawn, int ySpawn, Facing face, SDL_Renderer*& renderer, Level*& level) : MovableEntity(xSpawn, ySpawn, 21, 11, 0.08f, level), state(IDLE), facing(face) {

	char* path = (char*)"res/images/moth.png";
	animations[IDLE][LEFT] = new Animation(path, 1, 1, 900, 35, 35, renderer);
	animations[IDLE][RIGHT] = new MirrorAnimation(path, 1, 1, 900, 35, 35, 0, renderer);
	animations[JUMP][LEFT] = new Animation(path, 1, 1, 900, 35, 35, renderer);
	animations[JUMP][RIGHT] = new MirrorAnimation(path, 1, 1, 900, 35, 35, 0, renderer);
}

Moth::~Moth() {
	for(int i(0); i<STATE_EOE; i++) {
		for(int j(0); j<FACING_EOE; j++) {
			delete animations[i][j];
		}
	}
}

void Moth::update(int delta) {
	if(state!=JUMP) { //si on est pas en plein saut on peut changer d'etat selon les touches activees
		if(!collidingGround) { //si on ne saute pas et qu'on ne touche plus le sol (chute libre)
			setState(JUMP);

		}
	} else if(collidingGround) {
		setState(IDLE);
	}

	//on update la position avec collision des objets solides
	MovableEntity::update(delta, state == JUMP);

	//on update l'animation
	animations[state][facing]->update(delta);
}

void Moth::render(SDL_Renderer*& renderer, int width, int height) {
	animations[state][facing]->render(renderer, x-7, y-24, width, height);

	// printHitBox(renderer, width, height);
}

void Moth::setState(State newState) {
	animations[state][facing]->init();

	state = newState;
}

void Moth::setFacing(Facing newFacing) {
	facing = newFacing;
}