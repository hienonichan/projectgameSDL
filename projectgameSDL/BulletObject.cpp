#include"BulletObject.h"

Bullet::Bullet(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){

	if (GameObject::CheckFlip() == SDL_FLIP_NONE) {
		velocity.setX(3);
	}
	else {
		velocity.setX(-3);
	}
}

void Bullet::draw() {
	GameObject::draw();
}

void Bullet::update() {
	GameObject::update();
}

void Bullet::clean() {

}