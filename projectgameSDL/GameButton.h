#ifndef __GameButton__
#define __GameButton__
#include"GameObject.h"
#include<string>

class GameButton :public GameObject {
public:
	GameButton(std::string id, int x, int y, int w, int h,int framecount,void(*callback)());
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	void(*button_callback)();
};
#endif
