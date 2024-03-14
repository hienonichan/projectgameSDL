#ifndef __SetupState__
#define __SetupState__

#include"State.h"
#include"GameObject.h"
#include<vector>
class SetupState :public State {

public:
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();


	virtual int getStateCode() { return code; }
private:
	int code = 4;
	std::vector<GameObject*>gameObjects;

};
#endif