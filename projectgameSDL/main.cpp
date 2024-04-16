#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"GameControl.h"
#include"SDL_ttf.h"
#include<SDL_mixer.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 640;

const int FPS = 100;
const int delay = 1000.0f / FPS;

int main(int argc, char* argv[]) {
	
	Uint32 mainstart, maintime;
	GameControl::getInstance()->init("window", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,false);

	while (GameControl::getInstance()->gRunning()) {
		mainstart = SDL_GetTicks();
		GameControl::getInstance()->handleEvents();
		GameControl::getInstance()->update();
		GameControl::getInstance()->render();

		maintime = SDL_GetTicks() - mainstart;
		if (maintime<delay){
			SDL_Delay((int)(delay - maintime));
		}
	}
	GameControl::getInstance()->clean();
	return 0;
}