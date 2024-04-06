#include"Boss.h"

Boss::Boss(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){}

void Boss::update() {
	GameObject::update();
}

void Boss::draw() {
	sprite = int(SDL_GetTicks() / 100) % frame;
	GameObject::draw();
}

void Boss::clean() {
	GameObject::clean();
}