#include"PlayState.h"
#include<iostream>
#include"GameControl.h"
#include"Player.h"
#include"ObjectTextureManager.h"
#include"Enemy.h"
#include"InputChecker.h"
#include"DelayState.h"
#include"MapObject.h"
#include"Camera.h"
#include"CollisionChecker.h"
Map* map;


// cac bien dieu khien ham random
int ran_num = 0;
int next_create = 0;
bool check_ran = false;

// cac bien dieu khien sinh bullet
int next_bullet = 0;


void PlayState:: rand_enemy() {
	ran_num = rand() % 1000 + 1;
	if (ran_num<=10) {
		check_ran = true;
	}
	if (check_ran) {
		int time = SDL_GetTicks();
		if (time-next_create >= 3000) {
			enemys.push_back(new Enemy("enemy",ran_num, ran_num, 100, 80, 8 ));
			check_ran = false;
			next_create = time;
		}
	}
}


void PlayState::update() {
	// random tao enemy
	rand_enemy();

	// ham ban dan
	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_SPACE)) {
		int time = SDL_GetTicks();
		if (time - next_bullet >= 100) {
			Vector cam = Camera::getInstance()->GetPosition();
			bullets.push_back(new Bullet("bullet", player1->getPos().getX()-cam.getX(), player1->getPos().getY()-cam.getY(), 19, 19, 1));
			Mix_VolumeChunk(shootingsound, MIX_MAX_VOLUME / 4);
			Mix_PlayChannel(3, shootingsound, 0);
			next_bullet = time;
		}
	}



	// goi lop check bullet ban trung enemy
	for (int i = 0; i < enemys.size(); i++) {
		for (int j = 0; j < bullets.size(); j++) {
			if (CollisionChecker::getInstance()->CollisionBullet(enemys[i], bullets[j])) {
				check_enemy[enemys[i]] = 1;
				check_bullet[bullets[j]]= 1;
			}
		}
	}

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}

	// neu enemy con song thi update
	for (int i = 0; i < enemys.size(); i++) {
		if (check_enemy[enemys[i]] == 0) {
			enemys[i]->update();
			enemys[i]->set_follow(player1);
		}
	}


	// neu dan chua trung thi update
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			if (check_bullet[bullets[i]] == 0) {
				bullets[i]->update();
			}
		}
	}

	// ham clear object toi uu cho game
	clearBullet();
	clearEnemy();


	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_ESCAPE)) {
		GameControl::getInstance()->getStateManager()->addState(new DelayState());
	}
	Camera::getInstance()->Update();
}

void PlayState::render() {
	// ve truoc player
	
	map->DrawMap();

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
	for (int i = 0; i < enemys.size(); i++) {
		if (check_enemy[enemys[i]] == 0) {
			enemys[i]->draw();
		}
	}
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			if (check_bullet[bullets[i]] == 0) {
				bullets[i]->draw();
			}
		}
	}
}


bool PlayState::loadState() {
	map = new Map();
	// phat am thanh
	Mix_VolumeChunk(sound1, MIX_MAX_VOLUME / 3);
	PlayMusic();

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider run.png", "player",GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/zom2.png", "enemy", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider stand.png", "playerstand", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/bullet.png", "bullet", GameControl::getInstance()->getRenderer());
	player1 = new Player("player", 100, 100, 60, 60, 6);
	
	gameObjects.push_back(player1);

	// lay player lam trung tam camera
	Camera::getInstance()->SetTarget(player1->GetOrigin());

	std::cout << "loading playState\n";
	return true;
}

bool PlayState::exitState() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	ObjectTextureManager::getInstance()->eraseTexture("player");
	ObjectTextureManager::getInstance()->eraseTexture("enemy");
	ObjectTextureManager::getInstance()->eraseTexture("solider stand");
	std::cout << "exting playState\n";
	return true;
}


