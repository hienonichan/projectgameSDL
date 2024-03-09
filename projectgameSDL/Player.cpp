#include"Player.h"
#include"GameObject.h"

Player::Player(std::string id, int x, int y, int w, int h,int framecount):GameObject(id,x,y,w,h,framecount) {
	velocity.setX(1);
}

void Player::draw() {
	GameObject::draw();
}

void Player::update() {
	sprite = int(SDL_GetTicks() / 100) % frame;
	GameObject::update();
}

void Player::clean() {
	GameObject::clean();
}

