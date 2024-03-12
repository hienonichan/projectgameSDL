#ifndef __HomeState__
#define __HomeState__
#include"State.h"
#include<vector>
#include"GameObject.h"
#include"SDL_ttf.h"
class HomeState :public State{
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();

	virtual int getStateCode() { return code; }
private:
	int code = 1;
	std::vector<GameObject*>gameObjects;

	static void turnToPlay();
	static void turnToExit();

};



#endif