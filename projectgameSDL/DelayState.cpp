#include"GameObject.h"
#include"DelayState.h"
#include<iostream>
#include"GameControl.h"
#include"HomeState.h"
#include"ObjectTextureManager.h"
#include"GameButton.h"
#include"PlayState.h"

void DelayState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void DelayState::render() {


	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_background, NULL, NULL);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(),texture_home, NULL, &rect_home);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
}

bool DelayState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/continue.png", "continue", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/menu.png", "menu", GameControl::getInstance()->getRenderer());
	GameObject* button1 = new GameButton("continue", 480, 230,288 , 129, 1, turnToPlay);
	GameObject* button2 = new GameButton("menu", 480, 350, 287, 122, 1, turnToHome);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);


	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/source ttf/PixeloidSans-Bold.ttf", 30);
	textSurface = TTF_RenderText_Blended(font, "MONSTER KILLER", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);


	std::string background = "C:/projectgameSDL/projectgameSDL/source picture/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);

	surface_home = IMG_Load("C:/projectgameSDL/projectgameSDL/source picture/homepic.png");
	texture_home = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_home);
	std::cout << "loading delaySTate\n";
	return true;
}

bool DelayState::exitState() {
	ObjectTextureManager::getInstance()->eraseTexture("continue");
	ObjectTextureManager::getInstance()->eraseTexture("menu");

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(surface_background);
	SDL_FreeSurface(surface_home);

	SDL_DestroyTexture(texture_home);
	SDL_DestroyTexture(texture_background);
	SDL_DestroyTexture(textTexture);

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	std::cout << "exiting delayState\n";
	return true;
}


void DelayState::turnToHome() {
	Mix_HaltChannel(-1);
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	PlayState* check =static_cast<PlayState*>( loi[loi.size() - 2]);
	check->exitState();
	GameControl::getInstance()->getStateManager()->addState(new HomeState);
}


void DelayState::turnToPlay() {
	GameControl::getInstance()->getStateManager()->deleteState();
}

