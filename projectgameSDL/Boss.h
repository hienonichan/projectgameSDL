#ifndef __Boss__
#define __Boss__
#include"GameObject.h"
#include<string>
class Boss :public GameObject {
public:
	Boss(std::string id, int x, int y, int w, int h, int framecount);
	void draw();
	void update();
	void clean();

private:
	int health = 20;
};
#endif
