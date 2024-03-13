#include"Player.h"
#include"GameObject.h"
#include"InputChecker.h"

Player::Player(std::string id, int x, int y, int w, int h,int framecount):GameObject(id,x,y,w,h,framecount) {
	
}

void Player::draw() {
	GameObject::drawchar();
}

void Player::update() {
	velocity.setX(0);
	velocity.setY(0);
	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_A)) {
		velocity.setX(-0.3);
	}
	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_D)) {
		velocity.setX(0.3);
	}
	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_W)) {
		velocity.setY(-0.3);
	}
	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_S)) {
		velocity.setY(0.3);
	}


	origin->x = position.getX() +width / 2;
	origin->y = position.getY() + height / 2;


	sprite = int(SDL_GetTicks() / 100) % frame;
	GameObject::update();
}

void Player::clean() {
	GameObject::clean();
}

