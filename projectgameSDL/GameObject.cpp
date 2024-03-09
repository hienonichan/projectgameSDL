#include<SDL.h>
#include"GameObject.h"
#include"ObjectTextureManager.h"
#include"GameControl.h"



GameObject::GameObject(std::string id, int x, int y, int w, int h,int framecount) {
	textureID = id;
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	frame = framecount;
}


void GameObject::draw() {
	ObjectTextureManager::getInstance()->drawAnimation(textureID, xpos, ypos, width, height, sprite,GameControl::getInstance()->getRenderer());
}


void GameObject::update() {
	
}


void GameObject:: clean() {

}
