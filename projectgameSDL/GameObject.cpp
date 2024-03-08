#include<SDL.h>
#include"GameObject.h"
#include"ObjectTextureManager.h"
#include"GameControl.h"



GameObject::GameObject(std::string id, int x, int y, int w, int h) {
	textureID = id;
	xpos = x;
	ypos = y;
	width = w;
	height = h;
}


void GameObject::draw() {
	ObjectTextureManager::getInstance()->draw(textureID, xpos, ypos, width, height, GameControl::getInstance()->getRenderer());
}

void GameObject::update() {
	xpos += 1;
}

void GameObject:: clean() {

}
