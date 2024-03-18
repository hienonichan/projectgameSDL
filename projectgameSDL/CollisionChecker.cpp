#include"CollisionChecker.h"
#include"Camera.h"
CollisionChecker* CollisionChecker::instance = 0;


bool CollisionChecker::CollisionEnemy(GameObject* enemy, GameObject* player) {
	int lowSquare = enemy->getW()/4;

	Vector cam = Camera::getInstance()->GetPosition();
	int left1 = player->getPos().getX()-cam.getX();
	int right1 = player->getPos().getX() + player->getW()-cam.getX();
	int top1 = player->getPos().getY()-cam.getY();
	int under1 = player->getPos().getY() + player->getH()-cam.getY();

	int left2 = enemy->getPos().getX()-cam.getX();
	int right2 = enemy->getPos().getX() + enemy->getW()-cam.getX();
	int top2 = enemy->getPos().getY()-cam.getY();
	int under2 = enemy->getPos().getY() + enemy->getH()-cam.getY();

	if (left1+lowSquare >= right2) { return false; }
	if (left2+lowSquare >= right1) { return false; }
	if (under1 <= top2+lowSquare) { return false; }
	if (under2 <= top1+lowSquare) { return false; }

	return true;
}


bool CollisionChecker::CollisionBullet(GameObject* enemy, Bullet* bullet) {
	Vector cam = Camera::getInstance()->GetPosition();
	int lowSquare = enemy->getW()/4;


	int left1 = enemy->getPos().getX() - cam.getX();
	int right1 = enemy->getPos().getX() + enemy->getW()-cam.getX();
	int top1 = enemy->getPos().getY() - cam.getY();
	int under1 = enemy->getPos().getY() + enemy->getH()-cam.getY();

	int left2 = bullet->getPos().getX() ;
	int right2 = bullet->getPos().getX() + bullet->getW();
	int top2 = bullet->getPos().getY() ;
	int under2 = bullet->getPos().getY() + bullet->getH() ;

	if (left1+lowSquare >= right2) { return false; }
	if (left2 +lowSquare>= right1) { return false; }
	if (under1 <= top2+lowSquare) { return false; }
	if (under2 <= top1+lowSquare) { return false; }

	return true;
}