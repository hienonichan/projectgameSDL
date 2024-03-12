#include"GameControl.h"
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"ObjectTextureManager.h"
#include"GameObject.h"
#include"Player.h"
#include"Enemy.h"
#include"InputChecker.h"
#include"StateManager.h"
#include"HomeState.h"
#include"PlayState.h"
#include<SDL_ttf.h>
#include<SDL_mixer.h>
GameControl*GameControl::instance = 0;







bool GameControl::init(const char* title, int x, int y, int width, int height, bool choose) {
	if (SDL_Init(SDL_INIT_EVERYTHING)>=0) {
		int windowWay;
		if (choose == true) {
			windowWay = SDL_WINDOW_FULLSCREEN;
		}
		else {
			windowWay = SDL_WINDOW_SHOWN;
		}
		TTF_Init();
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		window = SDL_CreateWindow(title, x, y, width, height, windowWay);

		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
	}
	else {
		return false;
	}
	game_running = true;
	std::string background = "C:/projectgameSDL/projectgameSDL/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);

	GameControl::getInstance()->getStateManager()->addState(new HomeState());


	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/GloriousChristmas-BLWWB.ttf", 20);
	SDL_Color textColor = { 255,255,255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "MONSTER KILLER", textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_Rect textRect;
	textRect.x = 500;
	textRect.y = 100;
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	return true;
}


void GameControl::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture_background, NULL, NULL);

	GameControl::getInstance()->getStateManager()->render();
	
	SDL_RenderPresent(renderer);
}

void GameControl::update() {
	GameControl::getInstance()->getStateManager()->update();
}


void GameControl::handleEvents() {
	InputChecker::getInstance()->checkInput();
}

void GameControl::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}






