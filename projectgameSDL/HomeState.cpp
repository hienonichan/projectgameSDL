#include"HomeState.h"
#include<iostream>
#include"GameButton.h"
#include"ObjectTextureManager.h"
#include"PlayState.h"
#include"SDL_ttf.h"
#include"GameControl.h"
#include"SetupState.h"

GameObject* loading = nullptr;

void HomeState::update() {
	if (SDL_GetTicks() >= 3000) {
		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->update();
		}
	}
	else {
		loading->update();
	}
}


void HomeState::render() {
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_background, NULL, NULL);
	if (SDL_GetTicks() >= 3000) {
		SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_home, NULL, &rect_home);
		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->draw();
		}
		SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	}
	else {
		SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_logo, NULL, &rect_logo);
		loading->draw();
	}
}


bool HomeState::loadState() {
	Mix_VolumeChunk(sound, MIX_MAX_VOLUME / 10);
	PlayMusic();

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/play.png", "startbutton", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/exit.png", "exitbutton", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/load.png", "loading", GameControl::getInstance()->getRenderer());
	GameObject* play = new GameButton("startbutton", 500, 200, 230, 100, 2,turnToPlay);
	GameObject* exit = new GameButton("exitbutton", 500, 320, 230, 100, 2,turnToExit);
	gameObjects.push_back(play);
	gameObjects.push_back(exit);
	
    loading = new GameObject("loading", 480, 300, 320, 320, 7);
	loading->change_speedsprite(420);

	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/source ttf/PixeloidSans-Bold.ttf", 30);
	textSurface = TTF_RenderText_Blended(font, "MONSTER KILLER", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	std::string background = "C:/projectgameSDL/projectgameSDL/source picture/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);
   
	surface_home = IMG_Load("C:/projectgameSDL/projectgameSDL/source picture/homepic.png");
	texture_home = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_home);

	surface_logo = IMG_Load("C:/projectgameSDL/projectgameSDL/source picture/logo game.png");
	texture_logo = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_logo);

	std::cout << "loading HomeState\n";
	return true;    
}


bool HomeState::exitState() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	loading->clean();
	ObjectTextureManager::getInstance()->eraseTexture("startbutton");
	ObjectTextureManager::getInstance()->eraseTexture("exitbutton");
	ObjectTextureManager::getInstance()->eraseTexture("loading");

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(surface_background);
	SDL_FreeSurface(surface_home);
	SDL_FreeSurface(surface_logo);
	 
	SDL_DestroyTexture(texture_background);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(texture_home);
	SDL_DestroyTexture(texture_logo);

	Mix_FreeChunk(sound);
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