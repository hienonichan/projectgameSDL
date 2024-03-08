#include"Player.h"
#include"GameObject.h"

Player::Player(std::string id, int x, int y, int w, int h):GameObject(id,x,y,w,h) {}

void Player::draw() {
	GameObject::draw();
}


void Player::update() {
	sprite = int(SDL_GetTicks() / 100) % 6;
}

void Player::clean() {
	GameObject::clean();
}

