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
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_background, NULL, NULL);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
}

bool DelayState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/continue.png", "continue", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/menu.png", "menu", GameControl::getInstance()->getRenderer());
	GameObject* button1 = new GameButton("continue", 550, 200, 135, 58, 1, turnToPlay);
	GameObject* button2 = new GameButton("menu", 550, 260, 135, 57, 1, turnToHome);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);


	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/GloriousChristmas-BLWWB.ttf", 50);
	textSurface = TTF_RenderText_Blended(font, "MONSTER KILLER", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);


	std::string background = "C:/projectgameSDL/projectgameSDL/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);
	std::cout << "loading delaySTate\n";
	return true;
}

bool DelayState::exitState() {
	
	std::cout << "exiting delayState\n";
	return true;
}


void DelayState::turnToHome() {
	Mix_HaltChannel(-1);
	GameControl::getInstance()->getStateManager()->addState(new HomeState);
}


void DelayState::turnToPlay() {
	GameControl::getInstance()->getStateManager()->deleteState();
}

