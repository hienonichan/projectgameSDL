#ifndef _-ObjectTextureManager__
#define __ObjectTextureManager__
#include<SDL.h>
#include<SDL_image.h>
#include"GameControl.h"
#include<map>
#include<string>
class ObjectTextureManager {

public:
	static ObjectTextureManager* getInstance() {
		if (instance == 0) {
			instance = new ObjectTextureManager();
			return instance;
		}
		return instance;
	}
	void eraseTexture(std::string id) { TextureMap.erase(id); }

	bool loadTexture(std::string file, std::string id, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int width, int height,SDL_Renderer* renderer, SDL_RendererFlip = SDL_FLIP_NONE);
	void drawAnimation(std::string id, int x, int y, int width, int height, int sprite, SDL_Renderer* renderer, SDL_RendererFlip = SDL_FLIP_NONE);
	void drawTile(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip = SDL_FLIP_NONE);

private:
	ObjectTextureManager(){}
	std::map<std::string, SDL_Texture*>TextureMap;
	static ObjectTextureManager* instance;
};
#endif
