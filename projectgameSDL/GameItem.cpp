#include"GameItem.h"

GameItem::GameItem(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){}

void GameItem::draw() {
	GameObject::draw();
}


void GameItem::update() {
	GameObject::update();
}

void GameItem::clean() {
	GameObject::clean();
}

