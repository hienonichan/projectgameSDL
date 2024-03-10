#include"PlayState.h"
#include<iostream>
#include"GameControl.h"
#include"Player.h"
#include"ObjectTextureManager.h"
#include"Enemy.h"
void PlayState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void PlayState::render() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
}


bool PlayState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider run.png", "player",GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/zom2.png", "enemy", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider stand.png", "playerstand", GameControl::getInstance()->getRenderer());
	GameObject* player1 = new Player("player", 100, 100, 60, 60, 6);
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