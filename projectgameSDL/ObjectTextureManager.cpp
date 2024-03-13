#include"ObjectTextureManager.h"
#include<iostream>
#include"Camera.h"
ObjectTextureManager* ObjectTextureManager::instance = 0;


bool ObjectTextureManager::loadTexture(std::string file, std::string id, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(file.c_str());
	if (surface == 0) {
		std::cout << "have some error in load surface\n";
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == 0) {
		std::cout << "have some error in load texture\n";
		return false;
	}
	else {
		TextureMap[id] = texture;
		return true;
	}
}


void ObjectTextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flipImage) {
	SDL_Rect sourceRect;
	SDL_Rect desRect;

	sourceRect.x = 0;
	sourceRect.y = 0;

	sourceRect.w = desRect.w = width;
	sourceRect.h = desRect.h = height;

	desRect.x = x;
	desRect.y = y;
	SDL_RenderCopyEx(renderer, TextureMap[id], &sourceRect, &desRect, 0, 0,flipImage);
}



void ObjectTextureManager::drawAnimation(std::string id, int x, int y, int width, int height, int sprite, SDL_Renderer* renderer, SDL_RendererFlip flipImage) {
	SDL_Rect sourceRect;
	SDL_Rect desRect;

	sourceRect.x = width*sprite;
	sourceRect.y = 0;

	sourceRect.w = desRect.w = width;
	sourceRect.h = desRect.h = height;

	Vector cam = Camera::getInstance()->GetPosition();

	desRect.x = x;
	desRect.y = y;
	if (id == "player" || id == "enemy"||id=="playerstand") {
		desRect.x -= cam.getX();
		desRect.y -= cam.getY();
	}

	SDL_RenderCopyEx(renderer, TextureMap[id], &sourceRect, &desRect, 0, 0, flipImage);

}


void ObjectTextureManager::drawTile(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip) {
	SDL_Rect sourceRect;
	SDL_Rect desRect;

	sourceRect.x = 0;
	sourceRect.y = 0;

	sourceRect.w = desRect.w = width;
	sourceRect.h = desRect.h = height;

	Vector cam = Camera::getInstance()->GetPosition();


	desRect.x = x-cam.getX();
	desRect.y = y-cam.getY();

	SDL_RenderCopyEx(renderer, TextureMap[id], &sourceRect, &desRect, 0, 0, flip);
}