#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"

Enemy::Enemy(std::string id, int x, int y, int w, int h,int framecount) : GameObject(id, x, y, w, h,framecount) {
	
}

void Enemy::draw() {
	GameObject::draw();
}


void Enemy::update() {
	sprite = int(SDL_GetTicks() / speed_sprite) % frame;
	GameObject::update();
}

void Enemy::clean() {
	GameObject::clean();
}
