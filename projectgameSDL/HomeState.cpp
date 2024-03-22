#include"HomeState.h"
#include<iostream>
#include"GameButton.h"
#include"ObjectTextureManager.h"
#include"PlayState.h"
#include"SDL_ttf.h"
#include"GameControl.h"
#include"SetupState.h"

void HomeState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}

	
}


void HomeState::render() {
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_background, NULL, NULL);

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
   }

	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
}


bool HomeState::loadState() {
	Mix_VolumeChunk(sound, MIX_MAX_VOLUME / 2);
	PlayMusic();

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/play.png", "startbutton", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/exit.png", "exitbutton", GameControl::getInstance()->getRenderer());
	GameObject* play = new GameButton("startbutton", 500, 200, 230, 100, 2,turnToPlay);
	GameObject* exit = new GameButton("exitbutton", 500, 300, 230, 100, 2,turnToExit);
	gameObjects.push_back(play);
	gameObjects.push_back(exit);


	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/GloriousChristmas-BLWWB.ttf", 50);
	textSurface = TTF_RenderText_Blended(font, "MONSTER KILLER", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	std::string background = "C:/projectgameSDL/projectgameSDL/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);
   
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
	Mix_HaltChannel(0);
	GameControl::getInstance()->getStateManager()->addState(new SetupState());
	std::cout << "start button clicked\n";
}


void HomeState::turnToExit() {
	GameControl::getInstance()->quit();
	std::cout << "exit button clicked\n";
}