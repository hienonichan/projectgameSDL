#ifndef __Healthbar__
#define __Healthbar__
#include"GameObject.h"
class Healthbar :public GameObject {
public:
	Healthbar(std::string id, int x, int y, int w, int h, int framecount);
	void update(GameObject*enemy);
	void draw();
	void clean();
	
private:
	int max_w;
};

#endif
