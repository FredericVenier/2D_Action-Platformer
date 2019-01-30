#include "Player.hpp"

Player::Player(SDL_Renderer*& renderer, Level*& level) : MovableEntity(1.0f, 0.0f, 5, 29, 0.08f, level), state(IDLE), facing(RIGHT),
right(false), left(false), rightLeft(false), up(false), down(false), attack(false), cooldown(0), combo(0) {

	char* path = (char*)"res/images/spritesheet_main.png";
	animations[IDLE][LEFT] = new Animation(path, 1, 5, 250, 35, 35, renderer);
	animations[IDLE][RIGHT] = new Animation(path, 1, 5, 250, 35, 35, renderer);
	animations[RUN][LEFT] = new Animation(path, 3, 9, 100, 35, 35, renderer);
	animations[RUN][RIGHT] = new Animation(path, 2, 9, 100, 35, 35, renderer);
	animations[JUMP][LEFT] = new BlockedAnimation(path, 5, 2, 75, 35, 35, renderer);
	animations[JUMP][RIGHT] = new BlockedAnimation(path, 4, 2, 75, 35, 35, renderer);
	animations[SQUAT][LEFT] = new Animation(path, 6, 5, 300, 35, 35, renderer);
	animations[SQUAT][RIGHT] = new Animation(path, 6, 5, 300, 35, 35, renderer);
	animations[ATTACK_ONE][LEFT] = new Animation(path, 7, 6, 100, 70, 35, renderer);
	animations[ATTACK_TWO][LEFT] = new Animation(path, 8, 6, 100, 70, 35, renderer);
	animations[ATTACK_THREE][LEFT] = new Animation(path, 7, 6, 100, 70, 35, renderer);
	animations[ATTACK_ONE][RIGHT] = new Animation(path, 7, 6, 100, 70, 35, renderer);
	animations[ATTACK_TWO][RIGHT] = new Animation(path, 8, 6, 100, 70, 35, renderer);
	animations[ATTACK_THREE][RIGHT] = new Animation(path, 7, 6, 100, 70, 35, renderer);
	// animations[ATTACK_ONE][LEFT] = new MirrorAnimation(animations[ATTACK_ONE][RIGHT]);
	// animations[ATTACK_TWO][LEFT] = new MirrorAnimation(animations[ATTACK_TWO][RIGHT]);
	// animations[ATTACK_THREE][LEFT] = new MirrorAnimation(animations[ATTACK_THREE][RIGHT]);
}

Player::~Player() {
	for(int i(0); i<7; i++) {
		// std::cout << "test1" << std::endl;
		//delete animations[i][1];
		// std::cout << "test2" << std::endl;
		//delete animations[i][0];
		// std::cout << "test3" << std::endl;
	}

	std::cout << "test" << std::endl;
}


void Player::update(int delta, InputHandler*& inputHandler) {
	//on update les compteurs de temps
	cooldown -= delta;

	//on recupere les input
	inputHandler->update();
	updateInput(inputHandler);
	bool updateLeft = (left && !right) || (left && right && rightLeft);
	bool updateRight = (right && !left) || (left && right && !rightLeft);

	//on update l'etat en fonction des input
	State oldState(state);
	updateState(updateLeft, updateRight);
	if(oldState != state) { //on met la hitbox a jour si besoin
		if(state == SQUAT) {
			setHitBox(x, y+16, 6, 13); //quand on s'accroupit

		} else if(state == JUMP) {
			if(oldState == SQUAT) setHitBox(x, y-16, 5, 26); //quand on saute alors qu'on est accroupit
			else setHitBox(x, y, 5, 26); //si on saute et qu'on n'est pas accroupit

		} else {
			if(oldState == SQUAT) setHitBox(x, y-16, 5, 29); //si on etait accroupit et qu'on revient a la hitbox de base
			else if(oldState == JUMP) setHitBox(x, y, 5, 29); //si on sautait et qu'on revient a la hitbox de base
		}
	}

	//on fait bouger en fonction de l'etat
	moveX(updateLeft, updateRight);

	//on update la position avec collision des objets solides
	MovableEntity::update(delta, inputHandler, state == JUMP);

	//on effectue la collision sur les objets interactifs
	doObjectsCollision();

	//on update l'animation
	animations[state][facing]->update(delta);
}

void Player::render(SDL_Renderer*& renderer, int width, int height) {
	if(state==SQUAT) animations[state][facing]->render(renderer, x-15, y-22, width, height);
	else animations[state][facing]->render(renderer, x-15, y-6, width, height);

	//printHitBox(renderer, width, height);
}


void Player::updateInput(InputHandler*& inputHandler) {
	//haut
	up = inputHandler->keys[SDL_SCANCODE_SPACE];

	//bas
	down = inputHandler->keys[SDL_SCANCODE_S];

	//gauche
	if(inputHandler->keys[SDL_SCANCODE_A]) {
		if(!left) rightLeft = true;
		left = true;
	} else {
		left = false;
	}

	//droite
	if(inputHandler->keys[SDL_SCANCODE_D]) {
		if(!right) rightLeft = false;
		right = true;
	} else {
		right = false;
	}

	//attaque
	attack = inputHandler->keys[SDL_SCANCODE_K];
}

void Player::updateState(bool updateLeft, bool updateRight) {
	if(state!=JUMP) { //si on est pas en plein saut on peut changer d'etat selon les touches activees
		if(!collidingGround) {
			setState(JUMP);
			if (xVelocity<0) setFacing(LEFT);
			else setFacing(RIGHT);

		} else if ((attack || (state==ATTACK_ONE && combo==1) || (state==ATTACK_TWO && combo==2)) && cooldown<=0 && state!=ATTACK_THREE) { //si on attaque
			switch (combo) {
				case 0:
					setState(ATTACK_ONE);
					cooldown = 600;
					break;
				case 1:
					setState(ATTACK_TWO);
					cooldown = 600;
					break;
				case 2:
					setState(ATTACK_THREE);
					cooldown = 400;
					break;
				default:
					break;
			}

		} else if ((state==ATTACK_ONE || state==ATTACK_TWO || state==ATTACK_THREE) && cooldown>0) { //si on est en train d'attaquer
			if (attack && cooldown<=300) {
				switch (state) {
					case ATTACK_ONE:
						combo = 1;
						break;
					case ATTACK_TWO:
						combo = 2;
						break;
					default:
						break;
				}
			}

		} else if (up) { //si on saute
			setSpeedY(sqrt(2*GRAVITY*16)); //on set la valeur de la vitesse a la vitesse de depart du saut = (2*g*h_max)^1/2
			setState(JUMP);
			if (xVelocity<0) setFacing(LEFT);
			else setFacing(RIGHT);

		} else if (down) { //si on s'accroupit
			if (state!=SQUAT) setState(SQUAT);

		} else if (updateLeft) { //si on cours vers la gauche
			if (state!=RUN || facing!=LEFT) { 
				setState(RUN);
				setFacing(LEFT);
			}

		} else if (updateRight) { //si on court vers la droite
			if (state!=RUN || facing!=RIGHT) { 
				setState(RUN);
				setFacing(RIGHT);
			}

		} else if (state != IDLE) { //sinon idle
			setState(IDLE);
		}

	} else if(collidingGround) { //si on sautait et qu'il y a collision
		if (attack && cooldown <= 0) setState(ATTACK_ONE);
		else if(down) setState(SQUAT);
		else if (up && xVelocity <= 0 && !updateRight) { //si on enchaine les sauts on repasse en etat saut sans gain de vitesse sur x
			setState(JUMP);
			setFacing(LEFT);
			setSpeedY(sqrt(2*GRAVITY*16));
			setFallingTime(0);
		}
		else if (up && xVelocity > 0 && !updateLeft) {
			setState(JUMP);
			setFacing(RIGHT);
			setSpeedY(sqrt(2*GRAVITY*16));
			setFallingTime(0);
		}
		else if (updateLeft) {
			setState(RUN);
			setFacing(LEFT);
		} 
		else if (updateRight) {
			setState(RUN);
			setFacing(RIGHT);
		}
		else setState(IDLE);
	}
}


void Player::moveX(bool updateLeft, bool updateRight) {
	initSpeedX();

	switch(state) {
		case IDLE:
			horizontalDeceleration(0.71f);
			break;

		case RUN:
			if(facing == LEFT) horizontalMove(-1);
			else horizontalMove(1);
			break;

		case SQUAT:
			horizontalDeceleration(0.75f);
			break;

		case ATTACK_ONE:
			horizontalDeceleration(0.85f);
			break;

		case JUMP: {
			float coef(0.98f);
			if(facing == RIGHT) {
				if(updateRight) coef = 0.991f;
				else if(updateLeft) coef = 0.9f;

			} else {
				if(updateLeft) coef = 0.991f;
				else if(updateRight) coef = 0.9f;
			}
			horizontalDeceleration(coef);
			break;
		}

		default:
			break;
	}

	//si on est au moins en haut du saut, et qu'on a une faible vitesse alors on peut se donner une impulsion
	if ((state==JUMP) && xVelocity<0.03f && xVelocity>-0.03f) { 
		float coef(0.0f);
		if (updateLeft) coef = -0.25f;
		else if (updateRight) coef = 0.25f;
		horizontalMove(coef);
	}
}


void Player::setState(State newState) {
	// std::cout << state << " - " << facing << std::endl;
	animations[state][facing]->init();

	//si on etait en train d'attaquer et qu'on arrete alors il y a un cooldown
	if ((state == ATTACK_ONE || state == ATTACK_TWO || state == ATTACK_THREE) && newState!=ATTACK_ONE && newState!=ATTACK_TWO && newState!=ATTACK_THREE) {
		cooldown = 100;
		combo = 0;
	}

	state = newState;
}

void Player::setFacing(Facing newFacing) {
	facing = newFacing;
}

void Player::doObjectsCollision() {
	for(int i(0); i<level->getActualRoom()->getObjectsNbr(); i++) {
		if(isInside(level->getActualRoom()->getInteractiveObject(i))) { //s'il y a collision avec l'hitbox d'un objet
			//on regarde d'ou vient la collision
			//bool upLeft = level->getActualRoom()->getInteractiveObject(i)->contains(x, y);
			//bool upRight = level->getActualRoom()->getInteractiveObject(i)->contains(x+w, y);
			bool downLeft = level->getActualRoom()->getInteractiveObject(i)->contains(x, y+h);
			bool downRight = level->getActualRoom()->getInteractiveObject(i)->contains(x+w, y+h);

			if(isFalling() && (downLeft || downRight)) { //si on arrive par le haut sur l'objet
				if(level->getActualRoom()->getInteractiveObject(i)->getType() == InteractiveObject::SPRINGBOARD) { //si l'objet est un tremplin
					InteractiveObject* obj = level->getActualRoom()->getInteractiveObject(i);

					switch(obj->nextStep()) { //on fait avancer l'objet d'un cycle
						case 1:	//si on vient de toucher le tremplin, il se baisse et nous avec
							y = obj->getY()-h;
							setSpeedY(0.0f);
							initFallingTime();
							break;
						case 2: //si il remonte le booleen associe devient vrai
							initFallingTime();
							if(up) setSpeedY(sqrt(2*GRAVITY*57));
							else setSpeedY(sqrt(2*GRAVITY*19));
							break;
						default:
							break;

					}
				}
			}
		}
	}
}