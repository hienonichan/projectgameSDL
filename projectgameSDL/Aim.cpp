#include"Aim.h"
#include"GameObject.h"
#include"InputChecker.h"

Aim::Aim(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){}

void Aim::update() {
	Vector* check = InputChecker::getInstance()->getMousePostion();
	Vector bonus(width / 2, height / 2);
	position = *check-bonus;
}

void Aim::draw() {
	GameObject::draw();
}

void Aim::clean() {

}