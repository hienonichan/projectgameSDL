#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"

Enemy::Enemy(std::string id, int x, int y, int w, int h) : GameObject(id, x, y, w, h) {}

void Enemy::draw() {
	GameObject::draw();
}


void Enemy::update() {
	xpos -= 1;
}

void Enemy::clean() {
	GameObject::clean();
}
