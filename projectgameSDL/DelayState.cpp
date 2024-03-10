#include"GameObject.h"
#include"DelayState.h"
#include<iostream>
#include"GameControl.h"
#include"HomeState.h"
#include"ObjectTextureManager.h"
#include"GameButton.h"

void DelayState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void DelayState::render() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
}

bool DelayState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/continue.png", "continue", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/menu.png", "menu", GameControl::getInstance()->getRenderer());
	GameObject* button1 = new GameButton("continue", 300, 200, 135, 58, 1, turnToPlay);
	GameObject* button2 = new GameButton("menu", 300, 260, 135, 57, 1, turnToHome);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);
	std::cout << "loading delaySTate\n";
	return true;
}

bool DelayState::exitState() {
	
	std::cout << "exiting delayState\n";
	return true;
}


void DelayState::turnToHome() {
	GameControl::getInstance()->getStateManager()->addState(new HomeState);
}

void DelayState::turnToPlay() {
	GameControl::getInstance()->getStateManager()->deleteState();
}

