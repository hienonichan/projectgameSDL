#ifndef __CollisionChecker__
#define __CollisionChecker__
#include"GameObject.h"
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

private:
	CollisionChecker(){}
	static CollisionChecker* instance;
};

#endif
