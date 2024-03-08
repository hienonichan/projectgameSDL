#include"GameControl.h"
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
GameControl*GameControl::instance = 0;

bool GameControl::init(const char* title, int x, int y, int width, int height, bool choose) {
	if (SDL_Init(SDL_INIT_EVERYTHING)>=0) {
		std::cout << "have something error in init SDL\n";
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

	return true;
}


void GameControl::render() {

}

void GameControl::update() {

}


void GameControl::handleEvents() {

}

void GameControl::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}






