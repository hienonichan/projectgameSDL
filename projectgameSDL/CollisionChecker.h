#ifndef __CollisionChecker__
#define __CollisionChecker__
class CollisionChecker {
public:
	static CollisionChecker* getInstance() {
		if (instance == 0) {
			instance = new CollisionChecker();
			return instance;
		}
		return instance;
	}

private:
	CollisionChecker(){}
	static CollisionChecker* instance;
};

#endif
