#include<SDL.h>
#include"GameObject.h"
#include"ObjectTextureManager.h"
#include"GameControl.h"



GameObject::GameObject(std::string id, int x, int y, int w, int h,int framecount):position(0,0),velocity(0,0) {
	textureID = id;
	width = w;
	height = h;
	frame = framecount;
}


void GameObject::draw() {
	ObjectTextureManager::getInstance()->drawAnimation(textureID,(int)position.getX(),(int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer());
}


void GameObject::update() {
	position += velocity;
}


void GameObject:: clean() {

}
