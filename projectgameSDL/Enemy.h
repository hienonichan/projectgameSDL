#ifndef __Enemy__
#define __Enemy__
#include"GameObject.h"
#include<string>
#include"Camera.h"
#include"Healthbar.h"
class Enemy :public GameObject{

public:
	Enemy(std::string id, int x, int y, int w,int h,int framecount,int health,int type);
	void draw();
	void update(GameObject*player);
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
	int enemy_state() { return attack_state; }
private:
	int max_health;
	int health;
	Healthbar* healthbar = nullptr;
	bool attack_state = false;
	int id_enemy=0;
};
 
#endif
