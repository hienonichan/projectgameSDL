#include"GameButton.h"
#include"InputChecker.h"
#include"GameObject.h"
#include"Vector.h"

GameButton::GameButton(std::string id,int x,int y,int w,int h,int framecount,void callback()):GameObject(id,x,y,w,h,framecount),button_callback(callback){
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
			Mix_PlayChannel(1, sound, 0);
			SDL_Delay(250);
			button_callback();
		}
	}
	else {
		sprite = 0;
	}
}

void GameButton::clean() {

}