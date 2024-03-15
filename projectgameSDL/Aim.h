#ifndef __Aim__
#define __Aim__
#include"GameObject.h"
#include"Vector.h"
class Aim :public GameObject{
public:
	Aim(std::string id,int x, int y, int w, int h, int framecount);
	void draw();
	void update();
	void clean();

private:

	
};
#endif