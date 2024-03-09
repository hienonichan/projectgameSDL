#include"GameButton.h"
#include"InputChecker.h"
#include"GameObject.h"
#include"Vector.h"
GameButton::GameButton(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){
	sprite = 0;
}


void GameButton::draw() {
	GameObject::draw();
}


void GameButton::update() {
	Vector* mouse = InputChecker::getInstance()->getMousePostion();
	if (mouse->getX() > position.getX()
		&& mouse->getY() > position.getY()
		&& mouse->getX() < (position.getX() + width)
		&& mouse->getY() < (position.getY() + height)) {
		sprite = 1;
		if (InputChecker::getInstance()->checkClicked(LEFT)) {
			sprite = 2;
		}
	}
	else {
		sprite = 0;
	}
}

void GameButton::clean() {

}