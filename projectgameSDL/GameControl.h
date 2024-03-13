#ifndef __GameControl__
#define __GameControl__
#include<SDL.h>
#include<SDL_image.h>
#include"StateManager.h"
#include<SDL_mixer.h>
#include<SDL_ttf.h>
class GameControl {
public:

	static GameControl* getInstance() {
		if (instance == 0) {
			instance =new GameControl();
			return instance;
		}
		return instance;
	}
	bool  init(const char* title, int x, int y, int width, int height, bool choose);

	void render();
	void update();
	void handleEvents();
	void clean();

	void quit() {
		game_running = false;
	}

	bool gRunning() {
		return game_running;
	}

	SDL_Renderer* getRenderer() {
		return renderer;
	}

	StateManager* getStateManager() { return state; }

private:
	GameControl() {};
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface_background = nullptr;
	SDL_Texture* texture_background = nullptr;
	bool game_running = true;

	static GameControl* instance;

	StateManager* state = new StateManager();





	SDL_Color color = { 255,0,0 };
	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect = { 400,100,400,400 };


};

#endif
