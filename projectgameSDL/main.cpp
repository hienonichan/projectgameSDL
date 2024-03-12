#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"GameControl.h"
#include"SDL_ttf.h"
#include<SDL_mixer.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 640;

int main(int argc, char* argv[]) {
	std::cout << "test";
	GameControl::getInstance()->init("window", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,false);

	while (GameControl::getInstance()->gRunning()) {
		GameControl::getInstance()->handleEvents();
		GameControl::getInstance()->update();
		GameControl::getInstance()->render();
	}
	GameControl::getInstance()->clean();
	return 0;
}