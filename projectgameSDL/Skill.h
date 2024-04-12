#ifndef __Skill__
#define __Skill__
#include"GameObject.h"
#include<vector>
#include<string>
#include"InputChecker.h"
#include"GameControl.h"

class Skill :public GameObject {
public:
	Skill(std::string id, int x, int y, int w, int h, int framecount,char type);
	void update();
	void draw();
	void clean();
	bool cool_down(int cooldown);
private:
	char skill_type;
	bool turn_on = true;
	int next = 0;
};
#endif