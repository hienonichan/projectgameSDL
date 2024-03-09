#ifndef __HomeState__
#define __HomeState__
#include"State.h"
class HomeState :public State{
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();

private:

};



#endif