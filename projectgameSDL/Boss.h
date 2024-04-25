#ifndef __Boss__
#define __Boss__
#include"GameObject.h"
#include<string>
#include"Vector.h"
#include"Camera.h"
#include<vector>
#include"Enemy.h"
#include"Healthbar.h"
class Boss :public GameObject {
public:
	Boss(std::string id, int x, int y, int w, int h, int framecount);
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
		health-=dame;
	}

	void set_follow(GameObject* player) {
		velocity = (player->getPos() - position);
		velocity.setLength1();
		velocity /= 5;
	}

	void attack();



private:
	int max_health = 2000;
	int health = max_health;
	Healthbar* healthbar = nullptr;
};
#endif
