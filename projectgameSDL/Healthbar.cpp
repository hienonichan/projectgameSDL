
#include"Healthbar.h"
#include"Enemy.h"
#include"Boss.h"
Healthbar::Healthbar(std::string id, int x, int y, int w, int h, int framecount) :GameObject(id, x, y, w, h, framecount) {
        max_w = w;
}

void Healthbar::update(GameObject*enemy) {
	if (static_cast<Enemy*>(enemy)) {
		Enemy* loi = static_cast<Enemy*>(enemy);
		changeW(max_w*loi->getHealth()/loi->getMaxHealth());
     }
	else {
		Boss* loi = static_cast<Boss*>(enemy);
		changeW(max_w * loi->getHealth() / loi->getMaxHealth());
	}
}

void Healthbar::draw() {
	GameObject::draw();

}

void Healthbar::clean() {
	GameObject::clean();
}