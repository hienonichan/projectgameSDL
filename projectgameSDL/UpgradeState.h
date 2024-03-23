#ifndef __UpgradeState__
#define __UpgradeState__
#include"State.h"
#include<vector>
#include"GameObject.h"
#include"GameButton.h"


class UpgradeState :public State {
public:
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();

	int getStateCode(){ return code; }
private:
	int code = 5;
	std::vector<GameObject*>gameObjects;
	static void upgrade_health();
	static void upgrade_attack();
	static void upgrade_ammo();
};
#endif
