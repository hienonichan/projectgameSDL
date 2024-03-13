#include"PlayState.h"
#include<iostream>
#include"GameControl.h"
#include"Player.h"
#include"ObjectTextureManager.h"
#include"Enemy.h"
#include"InputChecker.h"
#include"DelayState.h"
#include"MapObject.h"

Map* map;
GameObject* player1 = nullptr;
int ran_num = 0;

int next_create = 0;
bool check_ran = false;

void PlayState:: rand_enemy() {
	ran_num = rand() % 1000 + 1;
	if (ran_num== 1) {
		check_ran = true;
	}
	if (check_ran) {
		int time = SDL_GetTicks();
		if (time-next_create >= 2000) {
			enemys.push_back(new Enemy("enemy",ran_num, ran_num, 100, 80, 8 ));
			check_ran = false;
			next_create = time;
		}
	}
}


void PlayState::update() {
	rand_enemy();


	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->update();
		enemys[i]->set_follow(player1);
	}

	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_ESCAPE)) {
		GameControl::getInstance()->getStateManager()->addState(new DelayState());
	}
}

void PlayState::render() {
	// ve truoc player
	
	map->DrawMap();

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->draw();
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
	player1 = new Player("player", 100, 100, 60, 60, 6);
	GameObject* enemy1 = new Enemy("enemy", 400, 400, 100, 80, 8);


	gameObjects.push_back(player1);
	gameObjects.push_back(enemy1);
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
