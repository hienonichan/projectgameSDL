#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"

Enemy::Enemy(std::string id, int x, int y, int w, int h,int framecount,int heal) : GameObject(id, x, y, w, h,framecount) {
	max_health = heal;
	health = max_health;
	healthbar = new Healthbar("redbar", position.getX()+10, position.getY()-10, 40,5, 1);
}

void Enemy::draw() {
	GameObject::draw();
	healthbar->draw();
}


void Enemy::update() {
	//sprite = int(SDL_GetTicks() / speed_sprite) % frame;
    healthbar->update(this);
	healthbar->changePos(Vector(position.getX() + 15, position.getY() - 15));
	GameObject::update();
}

void Enemy::clean() {
	healthbar->clean();
	GameObject::clean();
}



