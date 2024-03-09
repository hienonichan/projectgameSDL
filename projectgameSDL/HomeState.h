#ifndef __HomeState__
#define __HomeState__
#include"State.h"
#include<vector>
#include"GameObject.h"
class HomeState :public State{
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();

private:
	std::vector<GameObject*>gameObjects;
};



#endif