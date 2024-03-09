#include"Player.h"
#include"GameObject.h"

Player::Player(std::string id, int x, int y, int w, int h,int framecount):GameObject(id,x,y,w,h,framecount) {}

void Player::draw() {
	GameObject::draw();
}

void Player::update() {
	sprite = int(SDL_GetTicks() / 100) % frame;
}

void Player::clean() {
	GameObject::clean();
}

