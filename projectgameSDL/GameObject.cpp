#include<SDL.h>
#include"GameObject.h"
#include"ObjectTextureManager.h"
#include"GameControl.h"
#include"InputChecker.h"
#include"Player.h"
SDL_RendererFlip check_flip = SDL_FLIP_NONE;

GameObject::GameObject(std::string id, int x, int y, int w, int h,int framecount):position(0,0),velocity(0,0) {
	position.setX(x);
	position.setY(y);
	textureID = id;
	width = w;
	height = h;
	frame = framecount;


	float px = x + w / 2;
	float py = y + h / 2;
	origin = new Point(px, py);
}


void GameObject::draw() {
	
	if (velocity.getX() > 0) {
		ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer());
	}
	else if (velocity.getX() < 0) {
		ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer(),SDL_FLIP_HORIZONTAL);
	}
	else {
		ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer());
	}
	

}


void GameObject::drawchar() {
	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_D)) {
		check_flip = SDL_FLIP_NONE;
	}
	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_A)) {
		check_flip = SDL_FLIP_HORIZONTAL;
	}

	if (velocity.getX() == 0 && velocity.getY() == 0) {
		GameObject::changeTexture("playerstand", 5);
		ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer(), check_flip);
	}
	else{
		GameObject::changeTexture("player", 6);
		ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer(), check_flip);
	}
}


void GameObject::update() {
	position += velocity;
}


void GameObject:: clean() {
	delete this;
}



int GameObject:: CheckFlip() { return check_flip; }

