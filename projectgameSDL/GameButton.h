#ifndef __GameButton__
#define __GameButton__
#include"GameObject.h"
#include<string>
#include<SDL_mixer.h>

class GameButton :public GameObject {
public:
	GameButton(std::string id, int x, int y, int w, int h,int framecount,void(*callback)());
	virtual void draw();
	virtual void update();
	virtual void clean();


private:
	void(*button_callback)();

	Mix_Chunk* sound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/clicksound.wav");

};
#endif
