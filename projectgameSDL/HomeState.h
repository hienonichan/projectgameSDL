#ifndef __HomeState__
#define __HomeState__
#include"State.h"
#include<vector>
#include"GameObject.h"
#include"SDL_ttf.h"
#include<SDL_mixer.h>

class HomeState :public State{
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();

	virtual int getStateCode() { return code; }

	void PlayMusic() {
		Mix_PlayChannel(0, sound, -1);
	}

private:
	int code = 1;
	std::vector<GameObject*>gameObjects;

	static void turnToPlay();
	static void turnToExit();

	Mix_Chunk* sound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/source_sound/theme sound.wav");


	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr;
	SDL_Color colorText = { 255,0,0 };
	SDL_Rect textRect = { 470,120,400,400 };

	SDL_Surface* surface_background = nullptr;
	SDL_Texture* texture_background = nullptr;

	SDL_Surface* surface_home = nullptr;
	SDL_Texture* texture_home = nullptr;
	SDL_Rect rect_home = { 275,50,692,500 };

	SDL_Surface* surface_logo = nullptr;
	SDL_Texture* texture_logo = nullptr;
	SDL_Rect rect_logo = { 420,100,433,162 };
};



#endif