#include"HomeState.h"
#include<iostream>
#include"GameButton.h"
#include"ObjectTextureManager.h"
#include"PlayState.h"

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
	GameObject* play = new GameButton("startbutton", 500, 200, 230, 100, 2,turnToPlay);
	GameObject* exit = new GameButton("exitbutton", 500, 300, 230, 100, 2,turnToExit);
	gameObjects.push_back(play);
	gameObjects.push_back(exit);

	std::cout << "loading HomeState\n";
	return true;
}


bool HomeState::exitState() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	ObjectTextureManager::getInstance()->eraseTexture("startbutton");
	ObjectTextureManager::getInstance()->eraseTexture("exitbutton");
	std::cout << "exiting HomeState\n";
	return true;
}


void HomeState::turnToPlay() {
	GameControl::getInstance()->getStateManager()->addState(new PlayState());
	std::cout << "start button clicked\n";
}


void HomeState::turnToExit() {
	GameControl::getInstance()->quit();
	std::cout << "exit button clicked\n";
}