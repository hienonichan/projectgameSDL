#ifndef __CollisionChecker__
#define __CollisionChecker__
#include"GameObject.h"
#include"BulletObject.h"
class CollisionChecker {
public:
	static CollisionChecker* getInstance() {
		if (instance == 0) {
			instance = new CollisionChecker();
			return instance;
		}
		return instance;
	}
	bool CollisionEnemy(GameObject* enemy, GameObject* player);
	bool CollisionBullet(GameObject* enemy, Bullet* bullet);

private:
	CollisionChecker(){}
	static CollisionChecker* instance;
};


#endif
