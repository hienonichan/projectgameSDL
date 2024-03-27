#ifndef __Player__
#define __Player__

#include<SDL.h>
#include"GameObject.h"
#include<string>
#include"GameOver.h"

class Player :public GameObject {
public:
	Player(std::string id,int x,int y,int w,int h,int framecount);
	void draw();
	void update();
	void clean();

	void death() {
		check_death = true;
		changeTexture("playerdeath", 8);
		sprite = 0;
		change_speedsprite(500);
		update();
		draw();
		if (sprite == 7) {
			GameControl::getInstance()->getStateManager()->addState(new GameOver());
		}
	}

};


#endif