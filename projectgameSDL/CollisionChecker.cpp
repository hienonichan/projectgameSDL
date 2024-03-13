#include"CollisionChecker.h"

bool CollisionChecker::CollisionEnemy(GameObject* enemy, GameObject* player) {
	int left1 = player->getPos().getX();
	int right1 = player->getPos().getX() + player->getW();
	int top1 = player->getPos().getY();
	int under1 = player->getPos().getY() + player->getH();

	int left2 = enemy->getPos().getX();
	int right2 = enemy->getPos().getX() + enemy->getW();
	int top2 = enemy->getPos().getY();
	int under2 = enemy->getPos().getY() + enemy->getH();

	if (left1 >= right2) { return false; }
	if (left2 >= right1) { return false; }
	if (under1 <= top2) { return false; }
	if (under2 <= top1) { return false; }

	return true;
}
