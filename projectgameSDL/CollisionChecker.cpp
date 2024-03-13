#include"CollisionChecker.h"
#include"Camera.h"

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


bool CollisionChecker::CollisionBullet(GameObject* enemy, Bullet* bullet) {
	Vector cam = Camera::getInstance()->GetPosition();
	int left1 = enemy->getPos().getX()-cam.getX();
	int righ1 = enemy->getPos().getX()  + enemy->getW() - cam.getX();
	int top1 = enemy->getPos().getY() - cam.getY();
	int under1 = enemy->getPos().getY()  + enemy->getH() - cam.getY();

	int left2 = bullet->getPos().getX() - cam.getX();
	int righ2 = bullet->getPos().getX() + bullet->getW() - cam.getX();
	int top2 = bullet->getPos().getY() - cam.getY();
	int under2 = bullet->getPos().getY() + bullet->getH() - cam.getY();



	return true;
}