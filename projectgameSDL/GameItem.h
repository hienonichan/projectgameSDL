#ifndef __GameItem__
#define __GameItem__
#include"GameObject.h"
#include<string>
class GameItem:public GameObject {
public:
	GameItem(std::string id,int x, int y, int w, int h, int framecount);
	void draw();
	void update();
	void clean();
private:
};
#endif
