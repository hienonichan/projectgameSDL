#include"BulletObject.h"


Bullet::Bullet(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){
	/*if (GameObject::CheckFlip() == SDL_FLIP_NONE) {
		velocity.setX(3);
	}
	else {
		velocity.setX(-3);

	}*/
}

void Bullet::draw() {
	GameObject::draw();
}

void Bullet::update() {
	sprite = int(SDL_GetTicks() / 100) % frame;
	GameObject::update();
}

void Bullet::clean() {

}