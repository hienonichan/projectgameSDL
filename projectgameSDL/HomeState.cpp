#include"HomeState.h"
#include<iostream>
#include"GameButton.h"
#include"ObjectTextureManager.h"

void HomeState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}


void HomeState::render() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
   }
}


bool HomeState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/play.png", "startbutton", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/exit.png", "exitbutton", GameControl::getInstance()->getRenderer());
	GameObject* play = new GameButton("startbutton", 500, 300, 230, 100, 2);

	GameObject* exit = new GameButton("exitbutton", 500, 400, 230, 100, 2);
	gameObjects.push_back(play);
	gameObjects.push_back(exit);

	std::cout << "loading HomeState\n";
	return true;
}


bool HomeState::exitState() {
	std::cout << "exiting HomeState\n";
	return true;
}