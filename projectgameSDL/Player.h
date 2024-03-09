#ifndef __Player__
#define __Player__

#include<SDL.h>
#include"GameObject.h"
#include<string>

class Player :public GameObject {
public:
	Player(std::string id,int x,int y,int w,int h,int framecount);
	void draw();
	void update();
	void clean();
};


#endif