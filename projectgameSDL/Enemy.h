#ifndef __Enemy__
#define __Enemy__
#include"GameObject.h"
#include<string>
class Enemy :public GameObject{

public:
	Enemy(std::string id, int x, int y, int w,int h);
	void draw();
	void update();
	void clean();

};
#endif
