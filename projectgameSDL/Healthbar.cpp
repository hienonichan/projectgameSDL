
#include"Healthbar.h"
#include"Enemy.h"
#include"Boss.h"
#include"Player.h"
Healthbar::Healthbar(std::string id, int x, int y, int w, int h, int framecount) :GameObject(id, x, y, w, h, framecount) {
        max_w = w;
}

void Healthbar::update(GameObject*enemy) {
	if (dynamic_cast<Enemy*>(enemy)) {
		Enemy* loi = dynamic_cast<Enemy*>(enemy);
		changeW(max_w * loi->getHealth() / loi->getMaxHealth());
		changePos(Vector(loi->getPos().getX() + 15,loi->getPos().getY() - 15));
	}
	else if(dynamic_cast<Boss*>(enemy)) {
		Boss* loi = dynamic_cast<Boss*>(enemy);
		changeW(max_w * loi->getHealth() / loi->getMaxHealth());
		changePos(Vector(loi->getPos().getX()+100,loi->getPos().getY() + 20));
	}
	else {
		Player* loi = dynamic_cast<Player*>(enemy);
		changeW(max_w * loi->getHealth() / loi->getMaxHealth());
	}
}

void Healthbar::draw() {
	GameObject::draw();
}

void Healthbar::clean() {
	GameObject::clean();
}