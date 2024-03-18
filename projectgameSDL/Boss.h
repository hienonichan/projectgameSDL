#ifndef __Boss__
#define __Boss__
#include"GameObject.h"
#include<string>
#include"Vector.h"
#include"Camera.h"
class Boss :public GameObject {
public:
	Boss(std::string id, int x, int y, int w, int h, int framecount);
	void draw();
	void update();
	void clean();

	int getHealth() {
		return health;
	}
	void lowHealth() {
		health--;
	}

	void set_follow(GameObject* player) {
		Vector cam = Camera::getInstance()->GetPosition();

		velocity = (player->getPos() - position);
		velocity.setLength1();
		velocity /= 20;
	}

private:
	int health = 10;
};
#endif
