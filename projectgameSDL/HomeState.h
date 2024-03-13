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

	Mix_Chunk* sound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/theme sound.wav");


};



#endif