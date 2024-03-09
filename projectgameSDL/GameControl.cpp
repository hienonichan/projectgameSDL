#include"GameControl.h"
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"ObjectTextureManager.h"
#include"GameObject.h"
#include"Player.h"
#include"Enemy.h"
GameControl*GameControl::instance = 0;




Player* character;
Enemy* monster;


bool GameControl::init(const char* title, int x, int y, int width, int height, bool choose) {
	if (SDL_Init(SDL_INIT_EVERYTHING)>=0) {
		int windowWay;
		if (choose == true) {
			windowWay = SDL_WINDOW_FULLSCREEN;
		}
		else {
			windowWay = SDL_WINDOW_SHOWN;
		}

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


	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider run.png", "player", renderer);
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/zom2.png", "enemy", renderer);
	character = new Player("player", 100, 100, 60, 60,6);
	monster = new Enemy("enemy", 300, 300, 100, 80,8);
	

	return true;
}


void GameControl::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture_background, NULL, NULL);


	character->draw();
	monster->draw();

	SDL_RenderPresent(renderer);
}

void GameControl::update() {
	character->update();
	monster->update();
}


void GameControl::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			game_running = false;
		}
	}
}

void GameControl::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}






