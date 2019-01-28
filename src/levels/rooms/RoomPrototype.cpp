#include "RoomPrototype.hpp"

RoomPrototype::RoomPrototype(SDL_Renderer*& renderer) : Room(26,21,11), cloudsNbr(10), cloudTimer(200000), lastCloudY(0.0f) {
	//fond
	backdropImg = new Image((char*)"res/images/level_prototype/backdrop.png", renderer);
	backdrop = new Sprite(backdropImg);

	//images
	cloudsSpriteSheet = new Image((char*)"res/images/level_prototype/cloudsSpriteSheet.png", renderer);
	for(int i(0); i<cloudsNbr; i++) {
		clouds.push_back(new Cloud(cloudsSpriteSheet, i));
	}

	//background
	backgroundImg = new Image((char*)"res/images/level_prototype/background.png", renderer);
	background = new Sprite(backgroundImg);

	//devant du decor
	frontgroundImg = new Image((char*)"res/images/level_prototype/frontground.png", renderer);
	frontground = new Sprite(frontgroundImg);

	//initialise le seed des nuages
	std::srand(std::time(NULL));

	//on ajoute les hitbox du sol
	addGround(new Entity(0.0f, 212.0f, 426, 32)); //sol
	addGround(new Entity(0.0f, -30.0f, 426, 30)); //plafond
	addGround(new Entity(-30.0f, 0.0f, 30, 240)); //mur gauche
	addGround(new Entity(426.0f, 0.0f, 30, 240)); //mur droit
	addGround(new Entity(256.0f, 156.0f, 101, 16)); //plateforme droite
	addGround(new Entity(100.0f, 151.0f, 101, 16)); //plateforme gauche

	//on ajoute les objets interactifs
	addInteractiveObject(new Springboard(238.0f, 204.0f, renderer));
}

RoomPrototype::~RoomPrototype() {
	delete backdropImg;
	delete backdrop;

	delete cloudsSpriteSheet;
	for(int i(0); i<cloudsNbr; i++) {
		delete clouds[i];
	}

	delete backgroundImg;
	delete background;

	delete frontgroundImg;
	delete frontground;
}

void RoomPrototype::update(int delta) {
	//on lance un nouveau nuage de facon aleatoire
	cloudTimer += delta;

	int r(((float)std::rand()/(float)RAND_MAX)*100.0f); //on tire un nombre alea entre 0 et 100
	if (r<cloudTimer/3000) {

		r = (((float)std::rand()/(float)RAND_MAX)*(float)(cloudsNbr-1)); //on tire un nombre alea entre 0 et le nombre de nuages-1
		if(clouds[r]->getX() == -clouds[r]->getW()-30) {

			//on tire un nombre alea entre 0.009 et 0.021 pour la vitesse du nuage
			float speed(((float)std::rand()/(float)RAND_MAX)*0.012f+0.009f);

			//on tire un nombre alea entre -10 et 110 pour la hauteur du nuage
			float y(((float)std::rand()/(float)RAND_MAX)*120.0f-10.0f);
			if (y<=lastCloudY-clouds[r]->getH() || y>=lastCloudY+clouds[r]->getH()) {
				clouds[r]->setY(y);
				clouds[r]->setSpeed(speed);

				cloudTimer = 0;
				lastCloudY = y;
			}
		}
	}

	//on update les nuages
	for(int i(0); i<cloudsNbr; i++) {
		clouds[i]->update(delta);
	}

	Room::update(delta);
}

void RoomPrototype::render(SDL_Renderer*& renderer, int width, int height, float playerX) {
	backdrop->render(renderer, 0, 0, width, height);

	for(int i(0); i<cloudsNbr; i++) {
		clouds[i]->render(renderer, (playerX-213)/10, width, height);
	}

	background->render(renderer, (playerX-213.0f)/7.0f, 0, width, height);

	frontground->render(renderer, (playerX-213.0f)/12.0f, 0, width, height);

	Room::render(renderer, width, height, playerX);
}