#ifndef __Enemy__
#define __Enemy__
#include"GameObject.h"
#include<string>
#include"Camera.h"
#include"Healthbar.h"
class Enemy :public GameObject{

public:
	Enemy(std::string id, int x, int y, int w,int h,int framecount,int health);
	void draw();
	void update();
	void clean();
	int getHealth() {
		return health;
	}
	int getMaxHealth() {
		return max_health;
	}
	void lowHealth(int dame) {
		health -= dame;
	}
	void set_follow(GameObject* player) {
		velocity = (player->getPos()- position);
		velocity.setLength1();
		velocity/=1;
	}
private:
	int max_health = 5;
	int health = max_health;
	Healthbar* healthbar = nullptr;
};

#endif
