#ifndef __Enemy__
#define __Enemy__
#include"GameObject.h"
#include<string>
#include"Camera.h"
class Enemy :public GameObject{

public:
	Enemy(std::string id, int x, int y, int w,int h,int framecount);
	void draw();
	void update();
	void clean();

	void set_follow(GameObject* player) {
		Vector cam = Camera::getInstance()->GetPosition();

		velocity = (player->getPos() - position);
		velocity.setLength1();
		velocity /= 20;
	}

};
#endif
