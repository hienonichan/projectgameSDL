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
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_home, NULL, &rect_home);

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
	GameObject* exit = new GameButton("exitbutton", 500, 320, 230, 100, 2,turnToExit);
	gameObjects.push_back(play);
	gameObjects.push_back(exit);


	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/PixeloidSans-Bold.ttf", 30);
	textSurface = TTF_RenderText_Blended(font, "MONSTER KILLER", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	std::string background = "C:/projectgameSDL/projectgameSDL/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);
   

	surface_home = IMG_Load("C:/projectgameSDL/projectgameSDL/homepic.png");
	texture_home = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_home);

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

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(surface_background);
	SDL_FreeSurface(surface_home);

	 
	SDL_DestroyTexture(texture_background);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(texture_home);

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