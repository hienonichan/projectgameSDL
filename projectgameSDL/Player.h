#ifndef __Player__
#define __Player__

#include<SDL.h>
#include"GameObject.h"
#include<string>
#include"GameOver.h"
#include"Skill.h"

class Player :public GameObject {
public:
	Player(std::string id,int x,int y,int w,int h,int framecount);
	void draw();
	void update();
	void clean();

	void death();

private:
	Skill* skill_q = nullptr;
	Skill* skill_e = nullptr;
};


#endif