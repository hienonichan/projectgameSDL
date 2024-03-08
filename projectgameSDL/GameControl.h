#ifndef __GameControl__
#define __GameControl__
#include<SDL.h>
#include<SDL_image.h>


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

private:
	GameControl() {};
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface_background = nullptr;
	SDL_Texture* texture_background = nullptr;
	bool game_running = true;

	static GameControl* instance;

	
};

#endif
