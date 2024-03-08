#ifndef __GameControl__
#define __GameControl__
#include<SDL.h>
#include<SDL_image.h>


class GameControl {
public:
	bool  init(const char* title, int x, int y, int width, int height, bool choose);

	void render();
	void update();
	void handleEvents();
	void clean();

	void quit() {

	}


	bool running() {
	    return 
	}
private:
	GameControl() {};
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface_background = nullptr;
	SDL_Texture* texture_background = nullptr;

	static GameControl* instance;

	
};

#endif
